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
	void AddStartVertex(const QPointF& point);
	std::shared_ptr<scShapeQtVisual> AddEndVertex(const QPointF& point);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, SELECT shapeType);
	bool CanCreateFace(const QPointF& currMousePos);

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::shared_ptr<scShapeQtVisual>> mShapeList;

	const QRect& mViewportSize;
	int mVertexCreatedCount;

	std::shared_ptr<scShapeQtVisual> mDrawStartVertex;
};
