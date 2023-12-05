#pragma once

class ShapeList;
class QPoint;
class State
{
public:
	State(ShapeList& shapeObjects);
	virtual ~State();

	virtual void MousePressEvent(QPoint& currMousePos) = 0;
	virtual void MouseMoveEvent(QPoint& currMousePos) = 0;
	virtual void KeyPressEvent() = 0;

protected:
	ShapeList& mShapeObjects;
};

