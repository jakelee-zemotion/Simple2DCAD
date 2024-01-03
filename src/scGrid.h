#pragma once

#include <list>
#include <memory>

class QRect;
class QPainter;
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
	const scCamera& mCamera;
	const QRect& mViewportSize;
	const std::shared_ptr<scCoordinateHelper> mCoordinateHelper;

	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
};

