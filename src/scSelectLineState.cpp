#include "scSelectLineState.h"
#include "scShapeList.h"

#include <qDebug>

scSelectLineState::scSelectLineState(scShapeList& shapeObjects)
	:scState(shapeObjects)
{
	mIsPressed = false;
	mPrevMousePos = { 0.0, 0.0 };
}

scSelectLineState::~scSelectLineState()
{
}

void scSelectLineState::MousePressEvent(QPointF& currMousePos)
{
	mIsPressed = true;

	for (const auto& line : mShapeObjects.mLineList)
	{

		if (line->HitTest(currMousePos))
		{
			qDebug() << "hit";
			mSelectedLine = line;
		}
	}

	mPrevMousePos = currMousePos;
}

void scSelectLineState::MouseMoveEvent(QPointF& currMousePos)
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
