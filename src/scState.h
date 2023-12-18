#pragma once
#include "scScene.h"

class QKeyEvent;
class QPointF;
class scState
{
public:
	scState(const std::shared_ptr<scScene>& scene);
	virtual ~scState();

	virtual void MousePressEvent(const QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(const QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent(QKeyEvent* event) = 0;

	virtual void EndState() = 0;

protected:
	const std::shared_ptr<scScene> mScene;
	QPointF mPrevMousePos;
};

