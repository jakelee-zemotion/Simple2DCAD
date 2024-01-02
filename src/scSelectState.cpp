#include "scSelectState.h"

#include "scScene.h"
#include "scShapeQtVisual.h"
#include "scVertexQtVisual.h"
#include "scFaceQtVisual.h"
#include "scControlVertexQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <qDebug>
#include <QKeyEvent>
#include <QPainter>

using namespace std;

scSelectState::scSelectState(
	const shared_ptr<scScene>& scene, 
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper,
	SHAPE_TYPE selectShapeType)
		:scState(scene, coordinateHelper), mSelectShapeType(selectShapeType)
{
	mIsMousePressed = false;
	mPrevMousePos = { 0.0, 0.0 };

	angle = 0.0;
}

scSelectState::~scSelectState()
{
}

void scSelectState::Paint(QPainter& painter)
{
	for (const auto& shape : mDrawShapeList)
	{
		shape->Paint(painter);
	}
}

void scSelectState::MousePressEvent(const scVector2D& currMousePos)
{
	mIsMousePressed = true;
	mPrevMousePos = currMousePos;
}

void scSelectState::MouseMoveEvent(const scVector2D& currMousePos)
{
	if (mIsMousePressed)
	{
		if (mCurrHighlightShape == nullptr)
			return;
		
		scVector2D targetPos = currMousePos;

		// Vertex snapping
		if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::VERTEX)
		{
			targetPos = SnapVertex(currMousePos, mCurrHighlightShape->GetID());

			shared_ptr<scVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scVertexQtVisual>(mCurrHighlightShape);

			selectedVertex->SetXY(targetPos);
		}
		else if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::ROTATE_CONTROL_VERTEX)
		{


			shared_ptr<scControlVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scControlVertexQtVisual>(mCurrHighlightShape);


			scVector2D BB = mCoordinateHelper->CameraToLocal(mPrevMousePos);
			scVector2D CC = mCoordinateHelper->CameraToLocal(targetPos);

			shared_ptr<scVertexQtVisual> centerVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexVector.back());
			scVector2D AA = mCoordinateHelper->WorldToLocal(centerVertex->mVertexData->GetPos(), centerVertex->mVertexData->GetTransform());

			double a = VectorHelper::length(BB, CC);
			double b = VectorHelper::length(AA, BB);
			double c = VectorHelper::length(CC, AA);

			//qDebug() << b * c;

			if (b * c == 0.0)
				return;

			double crossZ = VectorHelper::crossZ(BB - AA, CC - AA);
			double sinX = crossZ / (b * c);
			double aaa = asin(sinX);
			angle += aaa;


			selectedVertex->MoveFace(AA, mPrevMousePos, aaa);


		}
		else if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::SCALE_CONTROL_VERTEX)
		{



			shared_ptr<scScaleControlVertexQtVisual> selectedVertex =
				dynamic_pointer_cast<scScaleControlVertexQtVisual>(mCurrHighlightShape);


			int diagIdx = (static_cast<int>(selectedVertex->mBoxPos) + 2) % 4;

			shared_ptr<scScaleControlVertexQtVisual> diagVertex = dynamic_pointer_cast<scScaleControlVertexQtVisual>(mVertexVector[diagIdx]);

			scVector2D diagLocalCoord = mCoordinateHelper->WorldToLocal(diagVertex->mVertexData->GetPos(), diagVertex->mVertexData->GetTransform());

			scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetPos);
			scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(mPrevMousePos);

			targetLocalCoord -= diagLocalCoord;
			prevLocalCoord -= diagLocalCoord;

			scMatrix2D inverseRotateMatrix = MatrixHelper::InverseRotateMatrix(angle);

			targetLocalCoord = (inverseRotateMatrix * targetLocalCoord);
			prevLocalCoord = (inverseRotateMatrix * prevLocalCoord);

			double dx = targetLocalCoord.x / prevLocalCoord.x;
			double dy = targetLocalCoord.y / prevLocalCoord.y;



			selectedVertex->MoveFace({ dx, dy }, diagLocalCoord, angle);



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

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;

	SelectShape();
}

void scSelectState::KeyPressEvent(QKeyEvent* event)
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

void scSelectState::EndState()
{
	if (mPrevHighlightShape != nullptr)
		mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mCurrHighlightShape != nullptr)
		mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mPrevHighlightShape.reset();
	mCurrHighlightShape.reset();

	ResetSelected();
}

std::shared_ptr<scShapeQtVisual> scSelectState::HitTest(const scVector2D& currMousePos)
{
	for (const auto& vertex : mVertexVector)
	{
		if (vertex->HitTest(currMousePos)) 
		{
			return vertex;
		}
	}


	return mScene->HitTest(currMousePos, mSelectShapeType);
}

void scSelectState::ResetSelected()
{
	if (mSelectedShape == nullptr)
		return;

	mSelectedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
	{
		mVertexVector.clear();
		mDrawShapeList.clear();
	}

	mSelectedShape.reset();

}

void scSelectState::HightlightShape()
{
	// From outside to inside the shape.
	if (mPrevHighlightShape == nullptr && mCurrHighlightShape != nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mCurrHighlightShape->GetID())
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
	}
	// From inside the shape to outside.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape == nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mPrevHighlightShape->GetID())
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	// From inside one shape to inside another shape.
	else if (mPrevHighlightShape != nullptr && mCurrHighlightShape != nullptr)
	{
		if (mPrevHighlightShape->GetID() == mCurrHighlightShape->GetID())
			return;

		// From inside the selected shape(previous shape) to inside the current shape.
		if (mSelectedShape != nullptr && mSelectedShape->GetID() == mPrevHighlightShape->GetID())
		{
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
		}
		// From inside the previous shape to inside the the selected shape(current shape).
		else if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		{
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		}
		// If there is not a selected shape.
		else
		{
			mPrevHighlightShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
			mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::HIGHTLIGHT);
		}		 

	}
}

void scSelectState::SelectShape()
{
	if (mCurrHighlightShape == nullptr)
		return;

	if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
		return;

	if (mCurrHighlightShape->GetShapeType() != SHAPE_TYPE::VERTEX &&
		mCurrHighlightShape->GetShapeType() != SHAPE_TYPE::LINE &&
		mCurrHighlightShape->GetShapeType() != SHAPE_TYPE::FACE)
		return;


	// Reset mSelectedShape
	if (mSelectedShape != nullptr && mSelectedShape->GetID() != mCurrHighlightShape->GetID())
		ResetSelected();

	// Set mSelectedShape
	mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::SELECT);
	mSelectedShape = mCurrHighlightShape;



	if (mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
	{
		shared_ptr<scFaceQtVisual> selectedFace =
			dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);



		selectedFace->ResetControlVertices();


		vector<shared_ptr<scControlVertexQtVisual>> listsss = selectedFace->mControlVertexVector;
		for (const auto& ss : listsss)
		{
			mVertexVector.push_back(ss);
			mDrawShapeList.push_back(ss);
		}
	}
}
