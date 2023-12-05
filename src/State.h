#pragma once

class ShapeVector;
class QPoint;
class State
{
public:
	State(ShapeVector& shapeObjects);
	virtual ~State();

	virtual void MousePressEvent(QPoint& currMousePos) = 0;
	virtual void MouseMoveEvent(QPoint& currMousePos) = 0;
	virtual void KeyPressEvent() = 0;

protected:
	ShapeVector& mShapeObjects;
};

