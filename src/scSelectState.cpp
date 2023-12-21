#include "scSelectState.h"

#include "scScene.h"
#include "scShapeQtVisual.h"
#include "scVertexQtVisual.h"
#include "scFaceQtVisual.h"

#include <qDebug>
#include <QKeyEvent>

using namespace std;

scSelectState::scSelectState(const shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType)
	:scState(scene), mSelectShapeType(selectShapeType)
{
	mIsMousePressed = false;
	mPrevMousePos = { 0.0, 0.0 };
}

scSelectState::~scSelectState()
{
}

void scSelectState::MousePressEvent(const QPointF& currMousePos)
{
	mIsMousePressed = true;
	mPrevMousePos = currMousePos;
}

void scSelectState::MouseMoveEvent(const QPointF& currMousePos)
{
	
	if (mIsMousePressed)
	{
		if (mCurrHighlightShape == nullptr)
			return;

		QPointF dist = currMousePos - mPrevMousePos;


		// Vertex snapping
		if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::VERTEX)
		{
			dist = SnapVertex(currMousePos, mCurrHighlightShape->GetID());
		}


		if (mCurrHighlightShape->GetShapeType() == SHAPE_TYPE::FACE)
		{
			//double scaleX = currMousePos.x() / mPrevMousePos.x();
			//double scaleY = currMousePos.y() / mPrevMousePos.y();

			//shared_ptr<scFaceQtVisual> scaleFace = dynamic_pointer_cast<scFaceQtVisual>(mCurrShape);
			//scaleFace->ScaleFace(scaleX, scaleY);
			////qDebug() << currMousePos.x() << mPrevMousePos.x() << scaleX << scaleY;
			//mPrevMousePos = currMousePos;
			//return;
		}
		mPrevMousePos = currMousePos;

		mCurrHighlightShape->Move(dist.x(), dist.y());

		return;
	}


	mCurrHighlightShape = mScene->HitTest(currMousePos, mSelectShapeType);
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

		case Qt::Key_W:
		{
			if (mSelectedShape != nullptr && mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
			{
				shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
				transformFace->ScaleFace(1.1, 1.1);
			}
		}
		break;

		case Qt::Key_S:
		{
			if (mSelectedShape != nullptr && mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
			{
				shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
				transformFace->ScaleFace(0.9, 0.9);
			}
		}
		break;

		case Qt::Key_A:
		{
			if (mSelectedShape != nullptr && mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
			{
				shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
				transformFace->RotateFace(0.1);
			}
		}
		break;

		case Qt::Key_D:
		{
			if (mSelectedShape != nullptr && mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
			{
				shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
				transformFace->RotateFace(-0.1);
			}
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

void scSelectState::ResetSelected()
{
	if (mSelectedShape != nullptr)
		mSelectedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

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

	if (mSelectedShape != nullptr && mSelectedShape->GetID() != mCurrHighlightShape->GetID())
		ResetSelected();

	mCurrHighlightShape->SetShapeColorType(COLOR_TYPE::SELECT);
	mSelectedShape = mCurrHighlightShape;


	if (mSelectedShape->GetShapeType() == SHAPE_TYPE::FACE)
	{
		shared_ptr<scFaceQtVisual> selectedFace =
			dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);

		mScene->AddBoundingBoxOfFace(selectedFace);
	}
}
