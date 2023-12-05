#pragma once
#include "State.h"

class SelectState : public State
{
public:
	SelectState(ShapeVector& shapeObjects);
	~SelectState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void KeyPressEvent() override;

private:

};

