#include "scCoordinate.h"

scCoordinate::scCoordinate(const scCamera& camera, const QRect& viewportSize)
	:mCamera(camera), mViewportSize(viewportSize)
{
}

scCoordinate::~scCoordinate()
{
}
