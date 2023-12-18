#pragma once
#include "scCamera.h"

class scCoordinate
{
public:
	scCoordinate(const scCamera& camera, const QRect& viewportSize);
	~scCoordinate();

private:
	const scCamera& mCamera;
	const QRect& mViewportSize;
};

