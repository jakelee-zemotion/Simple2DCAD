#pragma once
#include "scState.h"
#include <memory>

class scShapeVector;
class scSelectState : public scState
{
public:
	scSelectState(scShapeVector& shapeObjects);
	~scSelectState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeVector& mShapeObjects;
	QPoint* mSelectedPoint = nullptr;

	bool mIsPressed;
};

