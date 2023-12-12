#pragma once
#include "scState.h"

class scScene;
class scDrawLineState : public scState
{
public:
	scDrawLineState(std::shared_ptr<scScene> scene);
	~scDrawLineState() override;

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	bool mIsDrawing; // Use in mouseReleaseEvent
};

