#pragma once
#include "scState.h"
#include "scLineQtVisual.h"

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
	std::shared_ptr<scLineQtVisual> mSelectedLine;

	bool mIsPressed;
};

