#pragma once
#include <list>
#include <QDebug>
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"


class scScene
{
public:
	scScene(const QRect& viewportSize);
	~scScene();

	void Render(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> AddVertex(const QPointF& point, bool isDrawing);
	void EndDrawing();
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, int shapeType);

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;

	const QRect& mViewportSize;
};
