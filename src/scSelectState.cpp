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
	mCurrShape = mScene->HitTest(currMousePos, mSelectShapeType);

	if (mPrevShape == nullptr && mCurrShape != nullptr)
	{
		mCurrShape->SetColor(Qt::red);
		mPrevShape = mCurrShape;
	}
	else if (mPrevShape != nullptr && mCurrShape == nullptr)
	{
		mPrevShape->SetColor(Qt::black);
		mPrevShape = mCurrShape;
	}
	else if (mPrevShape != nullptr && mCurrShape != nullptr
			&& mPrevShape->GetID() != mCurrShape->GetID())
	{
		mPrevShape->SetColor(Qt::black);
		mCurrShape->SetColor(Qt::red);

		mPrevShape = mCurrShape;
	}

	// mSelectedShape != nullptr
	/*if (mSelectedShape.use_count())
	{
		if (mIsMousePressed)
		{
			QPointF dist = currMousePos - mPrevMousePos;
			mPrevMousePos = currMousePos;

			mSelectedShape->MoveShape(dist.x(), dist.y());
		}

		return;
	}*/

}

void scSelectState::MouseReleaseEvent()
{
	mIsMousePressed = false;
}

void scSelectState::KeyPressEvent()
{
}
