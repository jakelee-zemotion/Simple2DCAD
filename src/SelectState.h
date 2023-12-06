#pragma once
#include "State.h"
#include <memory>

class SelectState : public State
{
public:
	SelectState(ShapeVector& shapeObjects);
	~SelectState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	ShapeVector& mShapeObjects;
	QPoint* mSelectedPoint = nullptr;

	bool mIsPressed;
};

