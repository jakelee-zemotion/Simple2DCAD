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
	void AddVertex(const QPointF& point, bool isDrawing);
	void EndDrawing();
	void MoveDrawingPoint(const QPointF& point);

	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
	std::list<std::shared_ptr<scVertexQtVisual>> mVertexList;

private:
	const QRect& mViewportSize;
};
