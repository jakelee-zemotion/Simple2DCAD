#pragma once
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scFaceQtVisual.h"
#include "scCommon.h"

#include <queue>
#include <list>
#include <QDebug>

class scScene
{
public:
	scScene(const QRect& viewportSize);
	~scScene();

	void Render(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> AddStartVertex(const QPointF& point);
	std::shared_ptr<scShapeQtVisual> AddEndVertex(const QPointF& point);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, SHAPE_TYPE shapeType, scShapeID noTestShapeID = scShapeID(false));
	int GetVertexCreatedCount() const;

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::weak_ptr<scShapeQtVisual>> mShapeList;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mLineIter;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mFaceIter;

	const QRect& mViewportSize;
	int mVertexCreatedCount;
};
