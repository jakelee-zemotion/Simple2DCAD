#include "scSelectVertexState.h"
#include "scScene.h"

#include <qDebug>

scSelectVertexState::scSelectVertexState(scScene& scene)
	:scState(scene)
{
	mIsPressed = false;
}

scSelectVertexState::~scSelectVertexState()
{
}

void scSelectVertexState::MousePressEvent(QPointF& currMousePos)
{
	mIsPressed = true;

	for (const auto& point : mScene.mVertexList)
	{

		if (point->HitTest(currMousePos))
		{
			mSelectedPoint = point;
		}
	}
}

void scSelectVertexState::MouseMoveEvent(QPointF& currMousePos)
{
	if (mIsPressed)
	{
		//qDebug() << mSelectedPoint.use_count();

		if (mSelectedPoint.use_count())
		{
			mSelectedPoint->SetX(currMousePos.x());
			mSelectedPoint->SetY(currMousePos.y());
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
