#pragma once
#include "scState.h"

class scScene;
class scDrawLineState : public scState
{
public:
	scDrawLineState(std::shared_ptr<scScene>& scene);
	~scDrawLineState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	QPointF mPrevMousePos;

	bool mIsDrawing; // Use in mouseReleaseEvent
};

