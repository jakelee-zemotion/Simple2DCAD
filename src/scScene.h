#pragma once
#include "scCommon.h"
#include "scShapeID.h"

#include <queue>
#include <list>
#include <QDebug>

class scCoordinateHelper;
class scShapeQtVisual;
class scVertexQtVisual;
class scFaceQtVisual;
class QPainter;
class scScene
{
public:
	scScene(const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scScene();

	void Render(QPainter& painter);

	std::shared_ptr<scVertexQtVisual> AddStartVertex(const QPointF& point);
	std::shared_ptr<scVertexQtVisual> AddEndVertex(const QPointF& point);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const QPointF& currMousePos, SHAPE_TYPE shapeType, scShapeID noTestShapeID = scShapeID(false));

	void AddBoundingBoxOfFace(const std::shared_ptr<scFaceQtVisual>& face);
	void RemoveBoundingBoxOfFace();

	int GetVertexCreatedCount() const;

private:
	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::weak_ptr<scShapeQtVisual>> mDrawShapeList;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertLineIter;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertFaceIter;

	const std::shared_ptr<scCoordinateHelper>& mCoordinateHelper;
	int mVertexCreatedCount;
};
