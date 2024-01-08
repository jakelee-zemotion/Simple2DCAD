#pragma once

// system
#include <vector>

// Simple2DCAD
#include "scState.h"
#include "scCommon.h"

// Forward Declaration
class scShapeQtVisual;
class scScene;
class scControlVertexQtVisual;

class scSelectAllState : public scState
{
// [Member function section]
public:
	scSelectAllState(const std::shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper, const scShapeType& selectShapeType);

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

// [Member variable section]
private:
	const scShapeType mSelectShapeType;

	std::shared_ptr<scShapeQtVisual> mPrevHighlightShape;
	std::shared_ptr<scShapeQtVisual> mCurrHighlightShape;

	std::shared_ptr<scShapeQtVisual> mSelectedShape;

	std::vector<std::shared_ptr<scControlVertexQtVisual>> mControlVertexVector;

	bool mIsMousePressed;
	double mAngleSum;
};

