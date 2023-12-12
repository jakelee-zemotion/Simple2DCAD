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

	for (const auto& line : mScene->mLineList)
	{

		if (line->HitTest(currMousePos))
		{
			qDebug() << "hit";
			mSelectedLine = line;
		}
	}

	mPrevMousePos = currMousePos;
}

void scSelectLineState::MouseMoveEvent(const QPointF& currMousePos)
{
	if (mIsPressed)
	{
		if (mSelectedLine.use_count())
		{
			QPointF dist = currMousePos - mPrevMousePos;
			mPrevMousePos = currMousePos;

			mSelectedLine->MoveLine(dist.x(), dist.y());
		}
	}
}

void scSelectLineState::MouseReleaseEvent()
{
	mIsPressed = false;
	mSelectedLine.reset();
}

void scSelectLineState::KeyPressEvent()
{
}
