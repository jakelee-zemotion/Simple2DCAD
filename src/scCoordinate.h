#pragma once
#include "scCamera.h"
#include "scTransform.h"
#include <QRect>

class scCoordinate
{
public:
	scCoordinate(const scCamera& camera, const QRect& viewportSize);
	~scCoordinate();

	// World -> Screen -> Local -> Camera
	std::pair<double, double> WorldToScreen(double x, double y);
	std::pair<double, double> ScreenToLoacl(double x, double y, scTransform& transform);
	std::pair<double, double> LocalToCamera(double x, double y);

	std::pair<double, double> WorldToCamera(double x, double y, scTransform& transform);
	
	// Camera -> Local -> Screen -> World
	std::pair<double, double> CameraToLocal(double x, double y);
	std::pair<double, double> LoaclToScreen(double x, double y, scTransform& transform);
	std::pair<double, double> ScreenToWorld(double x, double y);

	std::pair<double, double> CameraToWorld(double x, double y, scTransform& transform);

private:
	const scCamera& mCamera;
	const QRect& mViewportSize;
};

