#pragma once

#include "scMatrixVectorHelper.h"

#include <utility>
#include <memory>

class scCamera;
class scTransform;
class QRect;
class scCoordinateHelper
{
public:
	scCoordinateHelper(const QRect& viewportSize);
	~scCoordinateHelper();

	// World -> Screen -> Local -> Camera
	scVector2D WorldToScreen(double x, double y);
	scVector2D ScreenToLoacl(double x, double y, scTransform& transform);
	scVector2D LocalToCamera(double x, double y);

	scVector2D WorldToLocal(double x, double y, scTransform& transform);
	scVector2D WorldToCamera(double x, double y, scTransform& transform);

	scVector2D ScreenToCamera(double x, double y, scTransform& transform);
	
	// Camera -> Local -> Screen -> World
	scVector2D CameraToLocal(double x, double y);
	scVector2D LoaclToScreen(double x, double y, scTransform& transform);
	scVector2D ScreenToWorld(double x, double y);

	scVector2D CameraToWorld(double x, double y, scTransform& transform);
	scVector2D CameraToScreen(double x, double y, scTransform& transform);

private:
	const QRect& mViewportSize;
};

