#pragma once

#include "scMatrixVectorHelper.h"

#include <utility>

class scCamera;
class scTransform;
class QRect;
class scCoordinateHelper
{
public:
	scCoordinateHelper(scCamera& camera, const QRect& viewportSize);
	~scCoordinateHelper();

	// World -> Screen -> Local -> Camera
	std::pair<double, double> WorldToScreen(double x, double y);
	std::pair<double, double> ScreenToLoacl(double x, double y, scTransform& transform);
	std::pair<double, double> LocalToCamera(double x, double y);

	scVector2D WorldToCamera(double x, double y, scTransform& transform);
	
	// Camera -> Local -> Screen -> World
	std::pair<double, double> CameraToLocal(double x, double y);
	std::pair<double, double> LoaclToScreen(double x, double y, scTransform& transform);
	std::pair<double, double> ScreenToWorld(double x, double y);

	scVector2D CameraToWorld(double x, double y, scTransform& transform);

private:
	scCamera& mCamera;
	const QRect& mViewportSize;
};

