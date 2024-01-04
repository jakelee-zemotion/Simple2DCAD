#pragma once

// system
#include <deque>
#include <list>
#include <memory>

// Simple2DCAD
#include "scMatrixVectorHelper.h"

class QRect;
class QPainter;
class scVertexQtVisual;
class scLineQtVisual;
class scCoordinateHelper;
class scCamera;
class scShapeQtVisual;
class scGrid
{
public:
	scGrid(const std::shared_ptr<scCoordinateHelper>& coordinateHelper, const scCamera& camera, const QRect& viewportSize);
	~scGrid();

	void Paint(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos);

	void PanEvent();
	void ZoomEvent(int mouseDir);

private:
	void AddRemoveGridVertex();

	//const int mOffset = 1000;
	double mStride = 50.0;
	//const int mSize = mOffset / mStride * 2 + 1;
	//const int mDegree = 10;

	const scCamera& mCamera;
	const QRect& mViewportSize;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;

	std::list<std::list<std::shared_ptr<scVertexQtVisual>>> mGridVertexList2D;
	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
};

