#pragma once
#include "scState.h"

class scShapeList;
class scDrawLineState : public scState
{
public:
	scDrawLineState(scShapeList& shapeObjects);
	~scDrawLineState() override;

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	bool mIsDrawing; // Use in mouseReleaseEvent
};

