#pragma once
#include "scState.h"

#include <QPointF>

class scScene;
class scVertexQtVisual;
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

	void EndDrawing(bool createFaceFlag);
	bool CanCreateFace(const scVector2D& currMousePos) const;

private:
	std::shared_ptr<scVertexQtVisual> mDrawingVertex;
	std::shared_ptr<scVertexQtVisual> mDrawStartVertex;
	
	bool mIsDrawing;
};

