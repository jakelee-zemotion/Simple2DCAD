#include "scSelectLineState.h"

#include <qDebug>

using namespace std;

scSelectLineState::scSelectLineState(shared_ptr<scScene> scene)
	:scState(scene)
{
	mIsPressed = false;
	mPrevMousePos = { 0.0, 0.0 };
}

scSelectLineState::~scSelectLineState()
{
}

void scSelectLineState::MousePressEvent(const QPointF& currMousePos)
{
	mIsPressed = true;
	mPrevMousePos = currMousePos;

	mSelectedShape = mScene->HitTest(currMousePos, 1);
}

void scSelectLineState::MouseMoveEvent(const QPointF& currMousePos)
{
	if (mIsPressed && mSelectedShape.use_count())
	{
		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mSelectedShape->MoveShape(dist.x(), dist.y());
	}
}

void scSelectLineState::MouseReleaseEvent()
{
	mIsPressed = false;
	mSelectedShape.reset();
}

void scSelectLineState::KeyPressEvent()
{
}
