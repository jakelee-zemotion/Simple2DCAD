#include "scSelectAllState.h"

// qt
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

// Simple2DCAD
#include "scScene.h"
#include "scShapeQtVisual.h"
#include "scVertexQtVisual.h"
#include "scFaceQtVisual.h"
#include "scControlVertexQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scRotateControlVertexQtVisual.h"
#include "scCenterControlVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scSelectAllState::scSelectAllState(const shared_ptr<scScene>& scene, const shared_ptr<scCoordinateHelper>& coordinateHelper, const scShapeType& selectShapeType)
		:scState(scene, coordinateHelper), mSelectShapeType(selectShapeType)
{
	mIsMousePressed = false;
	mPrevMousePos = { 0.0, 0.0 };

	mAngleSum = 0.0;
}

scSelectAllState::~scSelectAllState()
{
}

void scSelectAllState::Paint(QPainter& painter)
{
	DrawBoundingBoxLine(painter);

	for (const auto& shape : mControlVertexVector)
	{
		shape->Paint(painter);
	}
}

void scSelectAllState::DrawBoundingBoxLine(QPainter& painter)
{
	if (!mControlVertexVector.empty())
	{
		QPen pen(Qt::darkGray);
		pen.setWidth(2);
		pen.setStyle(Qt::DotLine);
		painter.setPen(pen);

		for (int i = 0; i < 4; i++)
		{
			const int i_1 = (i + 1) % 4;

			const scVector2D startPos = mControlVertexVector[i]->GetXY();
			const scVector2D endPos = mControlVertexVector[i_1]->GetXY();

			const QPointF startVertex = { startPos.x, startPos.y };
			const QPointF endVertex = { endPos.x, endPos.y };

			const QLineF line(startVertex, endVertex);
			painter.drawLine(line);
		}
	}
}

void scSelectAllState::MousePressEvent(const scVector2D& currMousePos)
{
	mIsMousePressed = true;
	mPrevMousePos = currMousePos;
}

void scSelectAllState::MouseMoveEvent(const scVector2D& currMousePos)
{
	if (mIsMousePressed)
	{
		if (mCurrHighlightShape == nullptr)
			return;
		
		scVector2D targetPos = currMousePos;

		// Vertex snapping
		if (mCurrHighlightShape->GetShapeType() == scShapeType::VERTEX)
		{
			targetPos = SnapVertex(currMousePos, mCurrHighlightShape->GetID());

			shared_ptr<scVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scVertexQtVisual>(mCurrHighlightShape);

			selectedVertex->SetXY(targetPos);
		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::ROTATE_CONTROL_VERTEX)
		{


			shared_ptr<scControlVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scControlVertexQtVisual>(mCurrHighlightShape);


			scVector2D BB = mCoordinateHelper->CameraToLocal(mPrevMousePos);
			scVector2D CC = mCoordinateHelper->CameraToLocal(targetPos);

			shared_ptr<scControlVertexQtVisual> centerVertex = dynamic_pointer_cast<scControlVertexQtVisual>(mControlVertexVector.back());
			scVector2D AA = centerVertex->GetLocalXY();

			double a = scVectorHelper::length(BB, CC);
			double b = scVectorHelper::length(AA, BB);
			double c = scVectorHelper::length(CC, AA);

			if (b * c == 0.0)
				return;

			double crossZ = scVectorHelper::crossZ(BB - AA, CC - AA);
			double sinX = crossZ / (b * c);
			double angle = asin(sinX);
			mAngleSum += angle;


			selectedVertex->MoveFace(AA, mPrevMousePos, angle);


			for (const auto& ss : mControlVertexVector)
			{
				ss->MultiplyRotateXY(angle, AA.x, AA.y);
			}

		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::SCALE_CONTROL_VERTEX)
		{



			shared_ptr<scScaleControlVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scScaleControlVertexQtVisual>(mCurrHighlightShape);


			int diagIdx = (static_cast<int>(selectedVertex->GetBoxPosition()) + 2) % 4;

			shared_ptr<scScaleControlVertexQtVisual> diagVertex = dynamic_pointer_cast<scScaleControlVertexQtVisual>(mControlVertexVector[diagIdx]);

			scVector2D diagLocalCoord = diagVertex->GetLocalXY();

			scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetPos);
			scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(mPrevMousePos);
			
			scMatrix2D InverseTranslateMatrix = scMatrixHelper::InverseTranslateMatrix(diagLocalCoord.x, diagLocalCoord.y);
			scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(mAngleSum);

			targetLocalCoord = (inverseRotateMatrix * InverseTranslateMatrix * targetLocalCoord);
			prevLocalCoord = (inverseRotateMatrix * InverseTranslateMatrix * prevLocalCoord);

			scVector2D delta = targetLocalCoord / prevLocalCoord;
			

			selectedVertex->MoveFace(delta, diagLocalCoord, mAngleSum);


			for (const auto& ss : mControlVertexVector)
			{
				ss->MultiplyScaleXY(delta.x, delta.y, diagLocalCoord.x, diagLocalCoord.y, mAngleSum);
			}

		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::FACE)
		{
			mCurrHighlightShape->Move(targetPos, mPrevMousePos);

			if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
			{
				for (const auto& ss : mControlVertexVector)
				{
					ss->Move(targetPos, mPrevMousePos);
				}
			}
		}
		else
		{
			mCurrHighlightShape->Move(targetPos, mPrevMousePos);
		}


		mPrevMousePos = currMousePos;

		return;
	}


	mCurrHighlightShape = HitTest(currMousePos);
	HightlightShape();
	
	mPrevHighlightShape = mCurrHighlightShape;
}

void scSelectAllState::MouseReleaseEvent()
{
	mIsMousePressed = false;

	SelectShape();
}

void scSelectAllState::KeyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Escape:
		{
			ResetSelected();
		}
		break;
	}
}

void scSelectAllState::EndState()
{
	if (mPrevHighlightShape != nullptr)
		mPrevHighlightShape->SetShapeColorType(scColorType::DEFAULT);

	if (mCurrHighlightShape != nullptr)
		mCurrHighlightShape->SetShapeColorType(scColorType::DEFAULT);

	mPrevHighlightShape.reset();
	mCurrHighlightShape.reset();

	ResetSelected();
}

std::shared_ptr<scShapeQtVisual> scSelectAllState::HitTest(const scVector2D& currMousePos)
{
	for (const auto& vertex : mControlVertexVector)
	{
		if (vertex->HitTest(currMousePos)) 
		{
			return vertex;
		}
	}

	return mScene->HitTest(currMousePos, mSelectShapeType);
}

void scSelectAllState::ResetSelected()
{
	if (mSelectedShape == nullptr)
		return;

	mSelectedShape->SetShapeColorType(scColorType::DEFAULT);

	if (mSelectedShape->GetShapeType() == scShapeType::FACE)
	{
		shared_ptr<scFaceQtVisual> face = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
		face->SetTransformToXY();


		mControlVertexVector.clear();
		mAngleSum = 0.0;

	}

	mSelectedShape.reset();

}

void scSelectAllState::HightlightShape()
{
	// From outside to inside the shape.
	if (mPrevHighlightShape == nullptr && mCurrHighlightShape != nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mCurrHighlightShape->GetID())
			mCurrHighlightShape->SetShapeColorType(scColorType::HIGHTLIGHT);
	}
	// From inside the shape to outside.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape == nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mPrevHighlightShape->GetID())
			mPrevHighlightShape->SetShapeColorType(scColorType::DEFAULT);
	}
	// From inside one shape to inside another shape.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape != nullptr)
	{
		if (mPrevHighlightShape->GetID() == mCurrHighlightShape->GetID())
			return;

		// From inside the selected shape(previous shape) to inside the current shape.
		if (mSelectedShape != nullptr && mSelectedShape->GetID() == mPrevHighlightShape->GetID())
		{
			mCurrHighlightShape->SetShapeColorType(scColorType::HIGHTLIGHT);
		}
		// From inside the previous shape to inside the the selected shape(current shape).
		else if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		{
			mPrevHighlightShape->SetShapeColorType(scColorType::DEFAULT);
		}
		// If there is not a selected shape.
		else
		{
			mPrevHighlightShape->SetShapeColorType(scColorType::DEFAULT);
			mCurrHighlightShape->SetShapeColorType(scColorType::HIGHTLIGHT);
		}		 

	}
}

void scSelectAllState::SelectShape()
{
	if (mCurrHighlightShape == nullptr)
	{
		ResetSelected();
		return;
	}

	if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		return;

	if (mCurrHighlightShape->GetShapeType() != scShapeType::VERTEX &&
		mCurrHighlightShape->GetShapeType() != scShapeType::LINE &&
		mCurrHighlightShape->GetShapeType() != scShapeType::FACE)
		return;


	// Reset mSelectedShape
	if (mSelectedShape != nullptr && mSelectedShape->GetID() != mCurrHighlightShape->GetID())
		ResetSelected();

	// Set mSelectedShape
	mCurrHighlightShape->SetShapeColorType(scColorType::SELECT);
	mSelectedShape = mCurrHighlightShape;



	if (mSelectedShape->GetShapeType() == scShapeType::FACE)
	{
		shared_ptr<scFaceQtVisual> selectedFace =
			dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);



		scBoundingBox box = selectedFace->MakeBoundingBox();

		mControlVertexVector.clear();

		scVector2D bb;
		shared_ptr<scControlVertexQtVisual> ss;


		bb = mCoordinateHelper->LocalToCamera(box.topLeft);
		ss = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), bb, mAngleSum, scBoxPosition::TOP_LEFT, mCoordinateHelper);
		mControlVertexVector.push_back(ss);

		bb = mCoordinateHelper->LocalToCamera(box.topRight);
		ss = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), bb, mAngleSum, scBoxPosition::TOP_RIGHT, mCoordinateHelper);
		mControlVertexVector.push_back(ss);

		bb = mCoordinateHelper->LocalToCamera(box.bottomRight);
		ss = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), bb, mAngleSum, scBoxPosition::BOTTOM_RIGHT, mCoordinateHelper);
		mControlVertexVector.push_back(ss);

		bb = mCoordinateHelper->LocalToCamera(box.bottomLeft);
		ss = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), bb, mAngleSum, scBoxPosition::BOTTOM_LEFT, mCoordinateHelper);
		mControlVertexVector.push_back(ss);




		bb = mCoordinateHelper->LocalToCamera({ box.center.x, box.topLeft.y });
		ss = make_shared<scRotateControlVertexQtVisual>(selectedFace.get(), bb, mCoordinateHelper);
		mControlVertexVector.push_back(ss);



		bb = mCoordinateHelper->LocalToCamera(box.center);
		ss = make_shared<scCenterControlVertexQtVisual>(selectedFace.get(), bb, mCoordinateHelper);
		mControlVertexVector.push_back(ss);


	}
}
