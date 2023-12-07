#pragma once

class QPoint;
class scState
{
public:
	scState();
	virtual ~scState();

	virtual void MousePressEvent(QPoint& currMousePos) = 0;
	virtual void MouseMoveEvent(QPoint& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;
};

