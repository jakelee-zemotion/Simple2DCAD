#pragma once
#include "scStateInterface.h"

class scShapeList;
class scDrawLineState : public scStateInterface
{
public:
	scDrawLineState(scShapeList& shapeObjects);
	~scDrawLineState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeList& mShapeObjects;
	bool mIsDrawing; // Use in mouseReleaseEvent
};

