#pragma once
#include "State.h"

class DrawLineState : public State
{
public:
	DrawLineState(ShapeVector& shapeObjects);
	~DrawLineState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	ShapeVector& mShapeObjects;
	bool mIsDrawing; // Use in mouseReleaseEvent
};

