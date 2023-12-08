#pragma once
#include "scStateInterface.h"

class scShapeList;
class scDrawLineState : public scStateInterface
{
public:
	scDrawLineState(scShapeList& shapeObjects);
	~scDrawLineState();

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeList& mShapeObjects;
	bool mIsDrawing; // Use in mouseReleaseEvent
};

