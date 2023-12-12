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
	std::shared_ptr<scShapeQtVisual> GetSelectedVertex(const QPointF& currMousePos, int shapeType);
	std::shared_ptr<scShapeQtVisual> GetSelectedLine(const QPointF& currMousePos);

private:
	std::list<std::shared_ptr<scVertexQtVisual>> mVertexList;
	std::list<std::shared_ptr<scLineQtVisual>> mLineList;

	const QRect& mViewportSize;
};
