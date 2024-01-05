#pragma once

// system
#include <deque>
#include <list>
#include <memory>

// Simple2DCAD
#include "scMatrixVectorHelper.h"

// Forward Declaration
class QRect;
class QPainter;
class scVertexQtVisual;
class scLineQtVisual;
class scCoordinateHelper;
class scCamera;
class scShapeQtVisual;

class scGrid
{
// [Member function section]
public:
	scGrid(const std::shared_ptr<scCoordinateHelper>& coordinateHelper, const scCamera& camera, const QRect& viewportSize);
	~scGrid();

	void Paint(QPainter& painter);
	std::shared_ptr<scShapeQtVisual> HitTest(const scVector2D& currMousePos);

	void PanEvent();
	void ZoomEvent(int mouseDir);

private:
	void ZoomInGrid();
	void ZoomOutGrid();

	void RemoveAddGridVertex();
	void RemoveAddTopLeftGridVertex();
	void RemoveAddBottomRightGridVertex();

	// TopLeft
	void RemoveTopLeftGridVertex();
	void AddTopLeftGridVertex();

	// BottomRight
	void RemoveBottomRightGridVertex();
	void AddBottomRightGridVertex();

// [Member variable section]
private:
	const scCamera& mCamera;
	const QRect& mViewportSize;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;

	std::list<std::list<std::shared_ptr<scVertexQtVisual>>> mGridVertexList2D;
	std::list<std::shared_ptr<scLineQtVisual>> mLineList;

	double mStride;
};

