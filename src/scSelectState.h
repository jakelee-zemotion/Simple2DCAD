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

	void MousePressEvent(const scVector2D& currMousePos) override;
	void MouseMoveEvent(const scVector2D& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

private:
	void ResetSelected();
	void HightlightShape();

	void SelectShape();

	bool mIsMousePressed;
	SHAPE_TYPE mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevHighlightShape;
	std::shared_ptr<scShapeQtVisual> mCurrHighlightShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;

	double angle = 0.0;
};

