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
		mCurrShape->SetColor(Qt::red);
	}
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		mPrevShape->SetColor(Qt::black);
	}
	else if (mPrevShape != nullptr && mCurrShape != nullptr)
	{
		if (mPrevShape->GetID() == mCurrShape->GetID())
			return;

		mPrevShape->SetColor(Qt::black);
		mCurrShape->SetColor(Qt::red);
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
