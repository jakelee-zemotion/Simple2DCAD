#pragma once
#include "scShapeQtVisual.h"
#include "scheader.h"

#include <queue>
#include <list>
#include <QDebug>

struct ShapeDrawPriority
{
	bool operator()(const scShapeQtVisual& shape1, const scShapeQtVisual& shape2) const
	{
		return shape1.GetShapeType() < shape2.GetShapeType();
	}
};

class scScene
{
public:
	scScene(const QRect& viewportSize);
	~scScene();

	void Render(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> AddStartVertex(const QPointF& point);
	std::shared_ptr<scShapeQtVisual> AddEndVertex(const QPointF& point);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, SHAPE_TYPE shapeType);
	int GetVertexCreatedCount() const;

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::weak_ptr<scShapeQtVisual>> mShapeList;
	//std::list<std::priority_queue<std::weak_ptr<scShapeQtVisual>>> mShapeList;

	const QRect& mViewportSize;
	int mVertexCreatedCount;
};
