#include "scSelectState.h"
#include "scVertexQtVisual.h"
#include "scFaceQtVisual.h"

#include <qDebug>
#include <QKeyEvent>

using namespace std;

scSelectState::scSelectState(shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType)
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
		if (mPrevShape == nullptr)
			return;

		QPointF targetPos = currMousePos;
		if (mSelectShapeType == SHAPE_TYPE::VERTEX)
		{
			shared_ptr<scVertexQtVisual> snappedVertex = 
				dynamic_pointer_cast<scVertexQtVisual>(mScene->HitTest(currMousePos, mSelectShapeType, mPrevShape->GetID()));

			if (snappedVertex != nullptr)
			{
				targetPos = snappedVertex->MakeQPointF();
			}
		}


		QPointF dist = targetPos - mPrevMousePos;
		mPrevMousePos = targetPos;

		mPrevShape->MoveShape(dist.x(), dist.y());

		return;
	}
	mCurrShape = mScene->HitTest(currMousePos, mSelectShapeType);

	
	// From outside to inside the shape.
	if (mPrevShape == nullptr && mCurrShape != nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mCurrShape->GetID())
			mCurrShape->SetShapeColorType(COLOR_TYPE::PUT_ON);
	}
	// From inside the shape to outside.
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		// If there is not a selected shape or the selected shape is not the current shape.
		if (mSelectedShape == nullptr || mSelectedShape->GetID() != mPrevShape->GetID())
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	// From inside one shape to inside another shape.
	else if (mPrevShape != nullptr && mCurrShape != nullptr)
	{
		if (mPrevShape->GetID() == mCurrShape->GetID())
			return;

		// From inside the selected shape(previous shape) to inside the current shape.
		if (mSelectedShape != nullptr && mSelectedShape->GetID() == mPrevShape->GetID())
		{
			mCurrShape->SetShapeColorType(COLOR_TYPE::PUT_ON);
		}
		// From inside the previous shape to inside the the selected shape(current shape).
		else if (mSelectedShape != nullptr && mSelectedShape->GetID() == mCurrShape->GetID())
		{
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		}
		// If there is not a selected shape.
		else
		{
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
			mCurrShape->SetShapeColorType(COLOR_TYPE::PUT_ON);
		}

	}

	mPrevShape = mCurrShape;
}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;

	// Select the shape.
	if (mCurrShape == nullptr)
		return;

	mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
	if (mSelectShapeType == SHAPE_TYPE::FACE)
	{

	}


	if (mSelectedShape != nullptr && mSelectedShape->GetID() != mCurrShape->GetID())
		mSelectedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mSelectedShape = mCurrShape;
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
			if (mSelectShapeType == SHAPE_TYPE::FACE)
			{
				if (mSelectedShape != nullptr)
				{
					shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
					transformFace->ScaleFace(1.1, 1.1);

				}
			}
		}
		break;

		case Qt::Key_S:
		{
			if (mSelectShapeType == SHAPE_TYPE::FACE)
			{
				if (mSelectedShape != nullptr)
				{
					shared_ptr<scFaceQtVisual> transformFace = dynamic_pointer_cast<scFaceQtVisual>(mSelectedShape);
					transformFace->ScaleFace(0.9, 0.9);

				}
			}
		}
		break;
	}
}

void scSelectState::EndState()
{
	if (mPrevShape != nullptr)
		mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mCurrShape != nullptr)
		mCurrShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mPrevShape.reset();
	mCurrShape.reset();

	ResetSelected();
}

void scSelectState::ResetSelected()
{
	if (mSelectedShape != nullptr)
		mSelectedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mSelectedShape.reset();
}
