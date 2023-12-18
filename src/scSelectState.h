#pragma once
#include "scState.h"
#include "scCommon.h"

class scShapeQtVisual;
class scScene;
class scSelectState : public scState
{
public:
	scSelectState(const std::shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType);
	virtual ~scSelectState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

protected:
	void ResetSelected();
	void HightlightShape();

	bool mIsMousePressed;
	SHAPE_TYPE mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevShape;
	std::shared_ptr<scShapeQtVisual> mCurrShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;
};

