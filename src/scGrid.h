#pragma once

#include <vector>
#include <list>
#include <memory>

class QRect;
class QPainter;
class scVertexQtVisual;
class scLineQtVisual;
class scCoordinateHelper;
class scCamera;
class scGrid
{
public:
	scGrid(
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper, 
		const scCamera& camera, 
		const QRect& viewportSize);
	~scGrid();

	void Paint(QPainter& painter);

private:
	const int mOffset = 1000;
	const int mStride = 50;
	const int mSize = mOffset / mStride * 2 + 1;
	const int mDegree = 10;

	const scCamera& mCamera;
	const QRect& mViewportSize;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;

	std::vector<std::vector<std::shared_ptr<scVertexQtVisual>>> mGridVertexVector;
	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
};

