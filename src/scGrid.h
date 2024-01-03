#pragma once
#include "scMatrixVectorHelper.h"

#include <deque>
#include <list>
#include <memory>

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
	scGrid(
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper, 
		const scCamera& camera, 
		const QRect& viewportSize);
	~scGrid();

	void Paint(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos);

	void PanEvent();
	void ZoomEvent(int mouseDir);

private:
	//const int mOffset = 1000;
	const int mStride = 50;
	//const int mSize = mOffset / mStride * 2 + 1;
	//const int mDegree = 10;

	const scCamera& mCamera;
	const QRect& mViewportSize;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;

	std::deque<std::deque<std::shared_ptr<scVertexQtVisual>>> mGridVertexDeque;
	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
};

