#pragma once
#include "scCommon.h"
#include "scShapeID.h"

#include <queue>
#include <list>
#include <QDebug>

class scCoordinateHelper;
class scShapeQtVisual;
class QPainter;
class scScene
{
public:
	scScene(const std::shared_ptr<scCoordinateHelper>& coordinate);
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

	const std::shared_ptr<scCoordinateHelper>& mCoordinate;
	int mVertexCreatedCount;
};
