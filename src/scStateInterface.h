#pragma once

class QPoint;
class scStateInterface
{
public:
	virtual void MousePressEvent(QPoint& currMousePos) = 0;
	virtual void MouseMoveEvent(QPoint& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;

	virtual ~scStateInterface() = 0 {};
};

