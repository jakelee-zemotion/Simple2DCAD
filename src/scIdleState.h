#pragma once
#include "scState.h"

class scIdleState : public scState
{
public:
	scIdleState();
	~scIdleState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;
};

