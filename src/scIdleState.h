#pragma once
#include "scStateInterface.h"

class scIdleState : public scStateInterface
{
public:
	scIdleState();
	~scIdleState();

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;
};

