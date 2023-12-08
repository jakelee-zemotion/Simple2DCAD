#pragma once

class QPointF;
class scStateInterface
{
public:
	virtual void MousePressEvent(QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;

	virtual ~scStateInterface() = 0 {};
};

