#include "SelectState.h"

SelectState::SelectState(ShapeList& shapeObjects)
	:State(shapeObjects)
{
}

SelectState::~SelectState()
{
}

void SelectState::MousePressEvent(QPoint& currMousePos)
{
}

void SelectState::MouseMoveEvent(QPoint& currMousePos)
{
}

void SelectState::KeyPressEvent()
{
}
