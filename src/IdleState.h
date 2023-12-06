#pragma once
#include "State.h"

class IdleState : public State
{
public:
	IdleState();
	~IdleState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void KeyPressEvent() override;
};

