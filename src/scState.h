#pragma once
#include "scMatrixVectorHelper.h"

#include <QPoint>
#include <memory>

class scShapeID;
class scScene;
class QKeyEvent;
class scState
{
public:
	scState(const std::shared_ptr<scScene>& scene);
	virtual ~scState();

	virtual void MousePressEvent(const QPointF& currMousePos) = 0;
	virtual void MouseMoveEvent(const QPointF& currMousePos) = 0;
	virtual void MouseReleaseEvent() = 0;
	virtual void KeyPressEvent(QKeyEvent* event) = 0;

	virtual void EndState() = 0;

protected:
	QPointF SnapVertex(const QPointF& currMousePos, const scShapeID& noTestShapeID);

	const std::shared_ptr<scScene> mScene;
	QPointF mPrevMousePos;
};

