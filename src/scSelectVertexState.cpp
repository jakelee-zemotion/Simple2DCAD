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

	for (const auto& point : mScene->mVertexList)
	{
		if (point->HitTest(currMousePos))
		{
			mSelectedPoint = point;
		}
	}

	mPrevMousePos = currMousePos;
}

void scSelectVertexState::MouseMoveEvent(const QPointF& currMousePos)
{
				   // mSelectedPoint != nullptr
	if (mIsPressed && mSelectedPoint.use_count())
	{
		QPointF dist = currMousePos - mPrevMousePos;
		mPrevMousePos = currMousePos;

		mSelectedPoint->SetXY(currMousePos.x(), currMousePos.y());
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
