#pragma once
#include "scScene.h"

class QPointF;
class scState
{
public:
	scState(std::shared_ptr<scScene>& scene);
	virtual ~scState();

	virtual void MousePressEvent(QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent() = 0;

protected:
	std::shared_ptr<scScene> mScene;
};

