#include "scSelectVertexState.h"

#include <qDebug>

using namespace std;

scSelectVertexState::scSelectVertexState(shared_ptr<scScene> scene)
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
}

void scSelectVertexState::MouseMoveEvent(const QPointF& currMousePos)
{
	if (mIsPressed)
	{
		//qDebug() << mSelectedPoint.use_count();

		if (mSelectedPoint.use_count())
		{
			mSelectedPoint->SetXY(currMousePos.x(), currMousePos.y());
		}
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
