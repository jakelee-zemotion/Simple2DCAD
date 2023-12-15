#include "scSelectState.h"
#include "scVertexQtVisual.h"

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
		// If there is not a clicked shape or the clicked shape is not the current shape.
		if (mClickedShape == nullptr || mClickedShape->GetID() != mCurrShape->GetID())
			mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
	}
	// From inside the shape to outside.
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		// If there is not a clicked shape or the clicked shape is not the current shape.
		if (mClickedShape == nullptr || mClickedShape->GetID() != mPrevShape->GetID())
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	// From inside one shape to inside another shape.
	else if (mPrevShape != nullptr && mCurrShape != nullptr)
	{
		if (mPrevShape->GetID() == mCurrShape->GetID())
			return;

		// From inside the clicked shape(previous shape) to inside the current shape.
		if (mClickedShape != nullptr && mClickedShape->GetID() == mPrevShape->GetID())
		{
			mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
		}
		// From inside the previous shape to inside the the clicked shape(current shape).
		else if (mClickedShape != nullptr && mClickedShape->GetID() == mCurrShape->GetID())
		{
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		}
		// If there is not a clicked shape.
		else
		{
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
			mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
		}

	}

	mPrevShape = mCurrShape;
}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;

	// Click the shape.
	if (mCurrShape == nullptr)
		return;

	mCurrShape->SetShapeColorType(COLOR_TYPE::CLICK);

	if (mClickedShape != nullptr && mClickedShape->GetID() != mCurrShape->GetID())
		mClickedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mClickedShape = mCurrShape;
}

void scSelectState::KeyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Escape:
		{
			ResetClicked();
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

	ResetClicked();
}

void scSelectState::ResetClicked()
{
	if (mClickedShape != nullptr)
		mClickedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mClickedShape.reset();
}
