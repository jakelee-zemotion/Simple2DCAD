#pragma once

// system
#include <memory>
#include <list>

// Simple2DCAD
#include "scCommon.h"
#include "scShapeID.h"
#include "scMatrixVectorHelper.h"

// Forward Declaration
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
// [Member function section]
public:
	scScene(const std::shared_ptr<scCoordinateHelper>& coordinateHelper, const std::shared_ptr<scGrid>& grid);

	void Render(QPainter& painter);

	std::shared_ptr<scVertexQtVisual> AddStartVertex(const scVector2D& pos);
	std::shared_ptr<scVertexQtVisual> AddEndVertex(const scVector2D& pos);
	void EndDrawing(bool canCreateFace);
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos, const scShapeType& shapeType, const scShapeID& noTestShapeID = scShapeID(0));

	void SaveData(const std::string& fileName);
	void LoadData(const std::string& fileName);
	void ClearData();

	int GetVertexCreatedCount() const;

// [Member variable section]
private:
	const std::shared_ptr<scCoordinateHelper>& mCoordinateHelper;
	const std::shared_ptr<scGrid>& mGrid;

	std::list<std::shared_ptr<scShapeQtVisual>> mVertexList;
	std::list<std::shared_ptr<scShapeQtVisual>> mLineList;
	std::list<std::shared_ptr<scShapeQtVisual>> mFaceList;

	std::list<std::weak_ptr<scShapeQtVisual>> mDrawShapeList;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertLineIter;
	std::list<std::weak_ptr<scShapeQtVisual>>::iterator mInsertFaceIter;

	int mVertexCreatedCount;
};
