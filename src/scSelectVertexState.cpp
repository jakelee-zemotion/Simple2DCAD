#include "scSelectVertexState.h"

#include <qDebug>

using namespace std;

scSelectVertexState::scSelectVertexState(shared_ptr<scScene>& scene)
	:scState(scene)
{
	mIsPressed = false;
}

scSelectVertexState::~scSelectVertexState()
{
}

void scSelectVertexState::MousePressEvent(const QPointF& currMousePos)
{
	mIsPressed = true;
	mPrevMousePos = currMousePos;

	mSelectedShape = mScene->HitTest(currMousePos, 0);
}

void scSelectVertexState::MouseMoveEvent(const QPointF& currMousePos)
{
				   // mSelectedShape != nullptr
	if (mIsPressed && mSelectedShape.use_count())
	{
		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mSelectedShape->MoveShape(dist.x(), dist.y());
	}
}

void scSelectVertexState::MouseReleaseEvent()
{
	mIsPressed = false;
	mSelectedShape.reset();
}

void scSelectVertexState::KeyPressEvent()
{
}
