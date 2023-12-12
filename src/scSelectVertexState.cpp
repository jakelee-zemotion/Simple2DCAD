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

	mSelectedPoint = mScene->GetSelectedVertex(currMousePos, 0);
}

void scSelectVertexState::MouseMoveEvent(const QPointF& currMousePos)
{
				   // mSelectedPoint != nullptr
	if (mIsPressed && mSelectedPoint.use_count())
	{
		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mSelectedPoint->MoveShape(dist.x(), dist.y());
	}
}

void scSelectVertexState::MouseReleaseEvent()
{
	mIsPressed = false;
	mSelectedPoint.reset();
}

void scSelectVertexState::KeyPressEvent()
{
}
