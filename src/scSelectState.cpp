#include "scSelectState.h"

#include <qDebug>

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

		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mPrevShape->MoveShape(dist.x(), dist.y());

		return;
	}


	mCurrShape = mScene->HitTest(currMousePos, mSelectShapeType);
	
	if (mPrevShape == nullptr && mCurrShape != nullptr)
	{
		if (!IsSameShape(mClickedShape, mCurrShape))
			mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
	}
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		if (!IsSameShape(mClickedShape, mPrevShape))
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	else if (mPrevShape != nullptr && mCurrShape != nullptr)
	{
		if (mPrevShape->GetID() == mCurrShape->GetID())
			return;


		if (IsSameShape(mClickedShape, mPrevShape))
		{
			mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
		}
		else if (IsSameShape(mClickedShape, mCurrShape))
		{
			mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		}
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


	if (mCurrShape == nullptr)
		return;

	mCurrShape->SetShapeColorType(COLOR_TYPE::CLICK);

	if (IsNotSameShape(mClickedShape, mCurrShape))
	{
		mClickedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}

	mClickedShape = mCurrShape;
}

void scSelectState::KeyPressEvent()
{
}

void scSelectState::EndState()
{
	if (mPrevShape != nullptr)
		mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mCurrShape != nullptr)
		mCurrShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	if (mClickedShape != nullptr)
		mClickedShape->SetShapeColorType(COLOR_TYPE::DEFAULT);

	mPrevShape.reset();
	mCurrShape.reset();
	mClickedShape.reset();
}

bool scSelectState::IsSameShape(
	shared_ptr<scShapeQtVisual>& shape1, 
	shared_ptr<scShapeQtVisual>& shape2)
{
	return shape1 != nullptr && shape2 != nullptr
		&& shape1->GetID() == shape2->GetID();
}

bool scSelectState::IsNotSameShape(
	shared_ptr<scShapeQtVisual>& shape1,
	shared_ptr<scShapeQtVisual>& shape2)
{
	return shape1 != nullptr && shape2 != nullptr
		&& shape1->GetID() != shape2->GetID();
}

