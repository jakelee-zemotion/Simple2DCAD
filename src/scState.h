#pragma once

class QPointF;
class scScene;
class scState
{
public:
	scState(scScene& scene);
	virtual ~scState();

	virtual void MousePressEvent(QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;

protected:
	scScene& mScene;
};

