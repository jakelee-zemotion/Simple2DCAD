#pragma once
#include "scShapeQtVisual.h"

#include <list>
#include <QDebug>

enum class SELECT
{
	VERTEX, LINE, FACE
};

class scScene
{
public:
	scScene(const QRect& viewportSize);
	~scScene();

	void Render(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> AddStartVertex(const QPointF& point);
	std::shared_ptr<scShapeQtVisual> AddEndVertex(const QPointF& point);
	void EndDrawing();
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, SELECT shapeType);
	bool CanCreateFace() const;

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;

	const QRect& mViewportSize;
	int mVertexCreatedCount;
};
