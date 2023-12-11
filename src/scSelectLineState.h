#pragma once
#include "scState.h"

class scSelectLineState : public scState
{
public:
	scSelectLineState(scShapeList& shapeObjects);
	~scSelectLineState() override;

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	bool mIsPressed;
};

