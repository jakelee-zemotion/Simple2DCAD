#pragma once
#include "scState.h"

#include <QPointF>

class scScene;
class scShapeQtVisual;
class scDrawLineState : public scState
{
public:
	scDrawLineState(const std::shared_ptr<scScene>& scene);
	~scDrawLineState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent(QKeyEvent* event) override;

	void EndState() override;

	bool CanCreateFace(const QPointF& currMousePos) const;

private:
	std::weak_ptr<scShapeQtVisual> mDrawingShape;
	std::weak_ptr<scShapeQtVisual> mDrawStartVertex;

	QPointF mStartVertexPos;
	bool mIsDrawing;
	bool mCanCreateFace;
};

