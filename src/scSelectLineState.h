#pragma once
#include "scState.h"
#include "scLineQtVisual.h"

class scSelectLineState : public scState
{
public:
	scSelectLineState(std::shared_ptr<scScene> scene);
	~scSelectLineState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	std::shared_ptr<scLineQtVisual> mSelectedLine;
	QPointF mPrevMousePos;

	bool mIsPressed;
};

