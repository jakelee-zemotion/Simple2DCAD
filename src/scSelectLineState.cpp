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
		}
	}
}

void scSelectLineState::MouseMoveEvent(QPointF& currMousePos)
{
	if (mIsPressed)
	{
	}
}

void scSelectLineState::MouseReleaseEvent()
{
	mIsPressed = false;
}

void scSelectLineState::KeyPressEvent()
{
}
