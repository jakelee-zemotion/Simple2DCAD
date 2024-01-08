#pragma once

// system
#include <utility>
#include <memory>

// Simple2DCAD
#include "scMatrixVectorHelper.h"

// Forward Declaration
class scCamera;
class scTransform;
class QRect;

class scCoordinateHelper
{
// [Member function section]
public:
	scCoordinateHelper(const scCamera& camera, const QRect& viewportSize);

	// World -> Screen -> Local -> Camera
	scVector2D WorldToScreen(const scVector2D& pos);
	scVector2D ScreenToLoacl(const scVector2D& pos, scTransform& transform);
	scVector2D LocalToCamera(const scVector2D& pos);

	scVector2D WorldToLocal(const scVector2D& pos, scTransform& transform);
	scVector2D WorldToCamera(const scVector2D& pos, scTransform& transform);

	scVector2D ScreenToCamera(const scVector2D& pos, scTransform& transform);
	
	// Camera -> Local -> Screen -> World
	scVector2D CameraToLocal(const scVector2D& pos);
	scVector2D LoaclToScreen(const scVector2D& pos, scTransform& transform);
	scVector2D ScreenToWorld(const scVector2D& pos);

	scVector2D CameraToWorld(const scVector2D& pos, scTransform& transform);
	scVector2D CameraToScreen(const scVector2D& pos, scTransform& transform);

// [Member variable section]
private:
	const scCamera& mCamera;
	const QRect& mViewportSize;
};

