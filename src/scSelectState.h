#pragma once
#include "scState.h"
#include "scCommon.h"

#include <list>
#include <memory>

class scShapeQtVisual;
class scScene;
class scSelectState : public scState
{
public:
	scSelectState(const std::shared_ptr<scScene>& scene, SHAPE_TYPE selectShapeType);
	virtual ~scSelectState() override;

	void Paint(QPainter& painter) override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

private:
	void ResetSelected();
	void HightlightShape();

	void SelectShape();

	void AddBoundingBoxOfFace(const std::shared_ptr<scFaceQtVisual>& face);
	void RemoveBoundingBoxOfFace();


	bool mIsMousePressed;
	SHAPE_TYPE mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevHighlightShape;
	std::shared_ptr<scShapeQtVisual> mCurrHighlightShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;


	std::list<std::shared_ptr<scShapeQtVisual>> mDrawShapeList;
};

