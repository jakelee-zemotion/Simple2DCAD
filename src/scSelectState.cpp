#include "scSelectState.h"

#include <qDebug>

using namespace std;

scSelectState::scSelectState(shared_ptr<scScene>& scene, SELECT selectShapeType)
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
		mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
	}
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
	}
	else if (mPrevShape != nullptr && mCurrShape != nullptr)
	{
		if (mPrevShape->GetID() == mCurrShape->GetID())
			return;

		mPrevShape->SetShapeColorType(COLOR_TYPE::DEFAULT);
		mCurrShape->SetShapeColorType(COLOR_TYPE::SELECT);
	}

	mPrevShape = mCurrShape;

}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;
}

void scSelectState::KeyPressEvent()
{
}
