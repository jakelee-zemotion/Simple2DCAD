#pragma once
#include "scStateInterface.h"
#include <memory>

class scShapeList;
class scSelectState : public scStateInterface
{
public:
	scSelectState(scShapeList& shapeObjects);
	~scSelectState();

	void MousePressEvent(QPoint& currMousePos) override;
	void MouseMoveEvent(QPoint& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeList& mShapeObjects;
	QPoint* mSelectedPoint = nullptr;

	bool mIsPressed;
};

