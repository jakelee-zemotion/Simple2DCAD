#pragma once
#include "scMatrixVectorHelper.h"

#include <memory>

class scShapeID;
class scScene;
class QKeyEvent;
class QPainter;
class scCoordinateHelper;
class scState
{
public:
	scState(const std::shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scState();

	virtual void Paint(QPainter& painter) = 0;
	//virtual std::shared_ptr<scShapeQtVisual> HitTest() = 0;

	virtual void MousePressEvent(const scVector2D& currMousePos) = 0;
	virtual void MouseMoveEvent(const scVector2D& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent(QKeyEvent* event) = 0;

	virtual void EndState() = 0;

protected:
	scVector2D SnapVertex(const scVector2D& currMousePos, const scShapeID& noTestShapeID);

	const std::shared_ptr<scScene> mScene;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;
	scVector2D mPrevMousePos;
};

