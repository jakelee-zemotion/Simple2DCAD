#pragma once
#include "scStateInterface.h"
#include "scVertexVisualInterface.h"
#include <memory>

class scShapeList;
class scSelectState : public scStateInterface
{
public:
	scSelectState(scShapeList& shapeObjects);
	~scSelectState();

	void MousePressEvent(QPointF& currMousePos) override;
	void MouseMoveEvent(QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	scShapeList& mShapeObjects;
	std::shared_ptr<scVertexVisualInterface> mSelectedPoint;

	bool mIsPressed;
};

