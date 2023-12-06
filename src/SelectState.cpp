#include "SelectState.h"
#include <qDebug>

SelectState::SelectState(ShapeVector& shapeObjects)
	:mShapeObjects(shapeObjects)
{
	mIsPressed = false;
}

SelectState::~SelectState()
{
}

void SelectState::MousePressEvent(QPoint& currMousePos)
{
	mIsPressed = true;
}

void SelectState::MouseMoveEvent(QPoint& currMousePos)
{
	if (mIsPressed)
	{
		qDebug() << "move";
	}
}

void SelectState::MouseReleaseEvent()
{
	mIsPressed = false;
}

void SelectState::KeyPressEvent()
{
}
