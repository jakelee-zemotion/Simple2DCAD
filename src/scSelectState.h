#pragma once
#include "scState.h"
#include "scCommon.h"

#include <list>
#include <vector>

class scShapeQtVisual;
class scScene;
class scSelectState : public scState
{
public:
	scSelectState(
		const std::shared_ptr<scScene>& scene, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper,
		SHAPE_TYPE selectShapeType);
	virtual ~scSelectState() override;

	void Paint(QPainter& painter) override;

	void MousePressEvent(const scVector2D& currMousePos) override;
	void MouseMoveEvent(const scVector2D& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

private:
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos);


	void ResetSelected();
	void HightlightShape();

	void SelectShape();

	bool mIsMousePressed;
	SHAPE_TYPE mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevHighlightShape;
	std::shared_ptr<scShapeQtVisual> mCurrHighlightShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;



	double angle = 0.0;

	std::vector<std::shared_ptr<scShapeQtVisual>> mVertexVector;
	std::list<std::shared_ptr<scShapeQtVisual>> mDrawShapeList;
};

