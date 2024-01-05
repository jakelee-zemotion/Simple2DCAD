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

			shared_ptr<scVertexQtVisual> selectedVertex = dynamic_pointer_cast<scVertexQtVisual>(mCurrHighlightShape);
			selectedVertex->SetXY(targetPos);
		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::ROTATE_CONTROL_VERTEX)
		{
			const shared_ptr<scRotateControlVertexQtVisual> selectedVertex = dynamic_pointer_cast<scRotateControlVertexQtVisual>(mCurrHighlightShape);

			const scVector2D B = mCoordinateHelper->CameraToLocal(mPrevMousePos);
			const scVector2D C = mCoordinateHelper->CameraToLocal(targetPos);

			const shared_ptr<scControlVertexQtVisual> centerVertex = dynamic_pointer_cast<scControlVertexQtVisual>(mControlVertexVector.back());
			const scVector2D A = centerVertex->GetLocalXY();

			const double a = scVectorHelper::length(B, C);
			const double b = scVectorHelper::length(A, B);
			const double c = scVectorHelper::length(C, A);

			if (b * c == 0.0)
				return;

			double crossZ = scVectorHelper::crossZ(B - A, C - A);
			double sinX = crossZ / (b * c);
			double angle = asin(sinX);
			mAngleSum += angle;

			// Rotate Face.
			selectedVertex->RotateFace(A, angle);

			// Rotate ControlVertices.
			for (const auto& controlVertex : mControlVertexVector)
			{
				controlVertex->MultiplyRotateXY(A, angle);
			}
		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::SCALE_CONTROL_VERTEX)
		{
			const shared_ptr<scScaleControlVertexQtVisual> selectedVertex = dynamic_pointer_cast<scScaleControlVertexQtVisual>(mCurrHighlightShape);

			const int diagIdx = (static_cast<int>(selectedVertex->GetBoxPosition()) + 2) % 4;
			const shared_ptr<scScaleControlVertexQtVisual> diagVertex = dynamic_pointer_cast<scScaleControlVertexQtVisual>(mControlVertexVector[diagIdx]);

			const scVector2D diagLocalCoord = diagVertex->GetLocalXY();

			const scMatrix2D InverseTranslateMatrix = scMatrixHelper::InverseTranslateMatrix(diagLocalCoord);
			const scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(mAngleSum);

			scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetPos);
			scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(mPrevMousePos);

			targetLocalCoord = (inverseRotateMatrix * InverseTranslateMatrix * targetLocalCoord);
			prevLocalCoord = (inverseRotateMatrix * InverseTranslateMatrix * prevLocalCoord);

			const scVector2D delta = targetLocalCoord / prevLocalCoord;
			
			// Scale Face.
			selectedVertex->ScaleFace(delta, diagLocalCoord, mAngleSum);

			// Scale ControlVertices.
			for (const auto& controlVertex : mControlVertexVector)
			{
				controlVertex->MultiplyScaleXY(delta, diagLocalCoord, mAngleSum);
			}
		}
		else if (mCurrHighlightShape->GetShapeType() == scShapeType::FACE)
		{
			mCurrHighlightShape->Move(targetPos, mPrevMousePos);

			if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrHighlightShape->GetID())
			{
				for (const auto& controlVertex : mControlVertexVector)
				{
					controlVertex->Move(targetPos, mPrevMousePos);
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
		const shared_ptr<scFaceQtVisual> selectedFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
		const scBoundingBox box = selectedFace->MakeBoundingBox();

		mControlVertexVector.clear();

		scVector2D boxVertexCoord;
		shared_ptr<scControlVertexQtVisual> controlVertex;

		// ScaleControlVertex
		boxVertexCoord = mCoordinateHelper->LocalToCamera(box.topLeft);
		controlVertex = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mAngleSum, scBoxPosition::TOP_LEFT, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);

		boxVertexCoord = mCoordinateHelper->LocalToCamera(box.topRight);
		controlVertex = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mAngleSum, scBoxPosition::TOP_RIGHT, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);

		boxVertexCoord = mCoordinateHelper->LocalToCamera(box.bottomRight);
		controlVertex = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mAngleSum, scBoxPosition::BOTTOM_RIGHT, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);

		boxVertexCoord = mCoordinateHelper->LocalToCamera(box.bottomLeft);
		controlVertex = make_shared<scScaleControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mAngleSum, scBoxPosition::BOTTOM_LEFT, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);

		// RotateControlVertex
		boxVertexCoord = mCoordinateHelper->LocalToCamera({ box.center.x, box.topLeft.y });
		controlVertex = make_shared<scRotateControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);

		// CenterControlVertex
		boxVertexCoord = mCoordinateHelper->LocalToCamera(box.center);
		controlVertex = make_shared<scCenterControlVertexQtVisual>(selectedFace.get(), boxVertexCoord, mCoordinateHelper);
		mControlVertexVector.push_back(controlVertex);
	}
}
