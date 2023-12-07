#pragma once
#include "scStateInterface.h"

class scIdleState : public scStateInterface
{
public:
	scIdleState();
	~scIdleState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;
};

