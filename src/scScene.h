#pragma once
#include <list>
#include <QDebug>
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"


class scScene
{
public:
	scScene() {};
	~scScene() {};

	void Render(QPainter& painter);
	void AddVertex(QPointF& point, bool isDrawing);
	void EndDrawing();
	void MoveDrawingPoint(QPointF& point);

	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
	std::list<std::shared_ptr<scVertexQtVisual>> mVertexList;

private:
	
};
