#pragma once
#include "State.h"

class DrawLineState : public State
{
public:
	DrawLineState(ShapeVector& shapeObjects);
	~DrawLineState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void KeyPressEvent() override;

private:
	bool mIsDrawing; // Use in mouseReleaseEvent

};

