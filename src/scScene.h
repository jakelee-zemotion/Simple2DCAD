#pragma once
#include "scCommon.h"
#include "scShapeID.h"
#include "scMatrixVectorHelper.h"

#include <memory>
#include <list>

class scCoordinateHelper;
class scShapeQtVisual;
class scVertexQtVisual;
class scFaceQtVisual;
class scCamera;
class scGrid;
class QPainter;
class QRect;
class scScene
{
public:
	scScene(const scCamera& camera, const QRect& viewportSize);
	~scScene();

	void Render(QPainter& painter);

	std::shared_ptr<scVertexQtVisual> AddStartVertex(const scVector2D& pos);
	std::shared_ptr<scVertexQtVisual> AddEndVertex(const scVector2D& pos);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos, SHAPE_TYPE shapeType, scShapeID noTestShapeID = scShapeID(false));

	void AddBoundingBoxOfFace(const std::shared_ptr<scFaceQtVisual>& face);
	void RemoveBoundingBoxOfFace();

	void SaveData();
	void LoadData();
	void ClearData();

	int GetVertexCreatedCount() const;

private:
	const scCamera& mCamera;
	const QRect& mViewportSize;

	std::shared_ptr<scCoordinateHelper> mCoordinateHelper;
	//std::shared_ptr<scGrid> mGrid;

	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::weak_ptr<scShapeQtVisual>> mDrawShapeList;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertLineIter;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertFaceIter;

	int mVertexCreatedCount;
};
