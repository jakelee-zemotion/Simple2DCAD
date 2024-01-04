#pragma once
#include "scState.h"
#include "scCommon.h"

#include <vector>

class scShapeQtVisual;
class scScene;
class scControlVertexQtVisual;
class scSelectState : public scState
{
public:
	scSelectState(
		const std::shared_ptr<scScene>& scene, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper,
		scShapeType selectShapeType);
	virtual ~scSelectState() override;

	void Paint(QPainter& painter) override;

	void MousePressEvent(const scVector2D& currMousePos) override;
	void MouseMoveEvent(const scVector2D& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

private:
	void DrawBoundingBoxLine(QPainter& painter);

	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos);


	void ResetSelected();
	void HightlightShape();

	void SelectShape();

	bool mIsMousePressed;
	scShapeType mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevHighlightShape;
	std::shared_ptr<scShapeQtVisual> mCurrHighlightShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;



	double mAngleSum;

	std::vector<std::shared_ptr<scControlVertexQtVisual>> mControlVertexVector;
};

