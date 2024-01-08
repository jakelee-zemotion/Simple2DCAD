#include "scCoordinateHelper.h"

// qt
#include <QRect>

// Simple2DCAD
#include "scCamera.h"
#include "scTransform.h"

using namespace std;

scCoordinateHelper::scCoordinateHelper(const scCamera& camera, const QRect& viewportSize)
	:mCamera(camera), mViewportSize(viewportSize)
{
}

scVector2D scCoordinateHelper::WorldToScreen(const scVector2D& pos)
{
    return pos;
}

scVector2D scCoordinateHelper::ScreenToWorld(const scVector2D& pos)
{
    return pos;
}

scVector2D scCoordinateHelper::ScreenToLoacl(const scVector2D& pos, scTransform& transform)
{
   const scVector2D scaleCoord = transform.Scale(pos);

    return scaleCoord;
}

scVector2D scCoordinateHelper::LoaclToScreen(const scVector2D& pos, scTransform& transform)
{
    const scVector2D scaleCoord = transform.UnScale(pos);

    return scaleCoord;
}

scVector2D scCoordinateHelper::LocalToCamera(const scVector2D& pos)
{
    const scVector2D zoomPanCoord = mCamera.ZoomPan(pos);

    return zoomPanCoord;
}

scVector2D scCoordinateHelper::CameraToLocal(const scVector2D& pos)
{
    const scVector2D zoomCoord = mCamera.UnZoomPan(pos);

    return zoomCoord;
}

scVector2D scCoordinateHelper::WorldToLocal(const scVector2D& pos, scTransform& transform)
{
    const scVector2D screenCoord = WorldToScreen(pos);
    const scVector2D localCoord = ScreenToLoacl(screenCoord, transform);

    return localCoord;
}

scVector2D scCoordinateHelper::WorldToCamera(const scVector2D& pos, scTransform& transform)
{
    const scVector2D screenCoord = WorldToScreen(pos);
    const scVector2D localCoord = ScreenToLoacl(screenCoord, transform);
    const scVector2D cameraCoord = LocalToCamera(localCoord);

    return cameraCoord;
}

scVector2D scCoordinateHelper::ScreenToCamera(const scVector2D& pos, scTransform& transform)
{
    const scVector2D localCoord = ScreenToLoacl(pos, transform);
    const scVector2D cameraCoord = LocalToCamera(localCoord);

    return cameraCoord;
}

scVector2D scCoordinateHelper::CameraToWorld(const scVector2D& pos, scTransform& transform)
{
    const scVector2D localCoord = CameraToLocal(pos);
    const scVector2D screenCoord = LoaclToScreen(localCoord, transform);
    const scVector2D worldCoord = ScreenToWorld(screenCoord);

    return worldCoord;
}

scVector2D scCoordinateHelper::CameraToScreen(const scVector2D& pos, scTransform& transform)
{
    const scVector2D localCoord = CameraToLocal(pos);
    const scVector2D screenCoord = LoaclToScreen(localCoord, transform);

    return screenCoord;
}

