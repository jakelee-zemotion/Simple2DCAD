#pragma once
#include "scState.h"
#include "scShapeQtVisual.h"
#include <memory>

class scSelectState : public scState
{
public:
	scSelectState(std::shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType);
	~scSelectState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

	void EndState() override;

private:
	bool IsSameShape(
		std::shared_ptr<scShapeQtVisual>& shape1, 
		std::shared_ptr<scShapeQtVisual>& shape2);
	bool IsNotSameShape(
		std::shared_ptr<scShapeQtVisual>& shape1,
		std::shared_ptr<scShapeQtVisual>& shape2);

	bool mIsMousePressed;
	SHAPE_TYPE mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevShape;
	std::shared_ptr<scShapeQtVisual> mCurrShape;

	std::shared_ptr<scShapeQtVisual> mClickedShape;
};

