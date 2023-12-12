#pragma once
#include "scState.h"
#include "scShapeQtVisual.h"
#include <memory>

class scShapeList;
class scSelectVertexState : public scState
{
public:
	scSelectVertexState(std::shared_ptr<scScene>& scene);
	~scSelectVertexState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	std::shared_ptr<scShapeQtVisual> mSelectedPoint;
	QPointF mPrevMousePos;

	bool mIsPressed;
};

