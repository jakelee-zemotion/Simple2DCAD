#pragma once
#include "scState.h"
#include <QPointF>

class scScene;
class scDrawLineState : public scState
{
public:
	scDrawLineState(std::shared_ptr<scScene>& scene);
	~scDrawLineState() override;

	void MousePressEvent(const QPointF& currMousePos) override;
	void MouseMoveEvent(const QPointF& currMousePos) override;
	void MouseReleaseEvent() override;
	void KeyPressEvent() override;

private:
	std::shared_ptr<scShapeQtVisual> mSelectedShape;
	QPointF mStartVertexPos;
	bool mIsDrawing;
	bool mCanCreateFace;

	std::shared_ptr<scShapeQtVisual> mStartVertex;
};

