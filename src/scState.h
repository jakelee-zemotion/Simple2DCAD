#pragma once

class QPointF;
class scShapeList;
class scState
{
public:
	scState(scShapeList& shapeObjects);
	virtual ~scState();

	virtual void MousePressEvent(QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;

protected:
	scShapeList& mShapeObjects;
};

