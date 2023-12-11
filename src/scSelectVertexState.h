#pragma once
#include "scStateInterface.h"
#include "scVertexVisualInterface.h"
#include <memory>

class scShapeList;
class scSelectVertexState : public scStateInterface
{
public:
	scSelectVertexState(scShapeList& shapeObjects);
	~scSelectVertexState();

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeList& mShapeObjects;
	std::shared_ptr<scVertexVisualInterface> mSelectedPoint;

	bool mIsPressed;
};

