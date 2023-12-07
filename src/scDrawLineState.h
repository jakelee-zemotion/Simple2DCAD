#pragma once
#include "scStateInterface.h"

class scShapeVector;
class scDrawLineState : public scStateInterface
{
public:
	scDrawLineState(scShapeVector& shapeObjects);
	~scDrawLineState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeVector& mShapeObjects;
	bool mIsDrawing; // Use in mouseReleaseEvent
};

