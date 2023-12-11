#include "scSelectLineState.h"
#include "scShapeList.h"

#include <qDebug>

scSelectLineState::scSelectLineState(scShapeList& shapeObjects)
	:scState(shapeObjects)
{
	mIsPressed = false;
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
}

void scSelectLineState::MouseMoveEvent(QPointF& currMousePos)
{
	if (mIsPressed)
	{
		mSelectedLine->MoveLine(1.0, 1.0);
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
