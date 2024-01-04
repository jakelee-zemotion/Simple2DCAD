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

scCoordinateHelper::~scCoordinateHelper()
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
    scVector2D scaleCoord = transform.Scale(pos.x, pos.y);

    return scaleCoord;
}

scVector2D scCoordinateHelper::LoaclToScreen(const scVector2D& pos, scTransform& transform)
{
    scVector2D scaleCoord = transform.UnScale(pos.x, pos.y);

    return scaleCoord;
}

scVector2D scCoordinateHelper::LocalToCamera(const scVector2D& pos)
{
    scVector2D zoomPanCoord = mCamera.ZoomPan(pos.x, pos.y);

    return zoomPanCoord;
}

scVector2D scCoordinateHelper::CameraToLocal(const scVector2D& pos)
{
    scVector2D zoomCoord = mCamera.UnZoomPan(pos.x, pos.y);

    return zoomCoord;
}

scVector2D scCoordinateHelper::WorldToLocal(const scVector2D& pos, scTransform& transform)
{
    scVector2D screenCoord = WorldToScreen(pos);
    scVector2D localCoord = ScreenToLoacl(screenCoord, transform);

    return localCoord;
}

scVector2D scCoordinateHelper::WorldToCamera(const scVector2D& pos, scTransform& transform)
{
    scVector2D screenCoord = WorldToScreen(pos);
    scVector2D localCoord = ScreenToLoacl(screenCoord, transform);
    scVector2D cameraCoord = LocalToCamera(localCoord);

    return cameraCoord;
}

scVector2D scCoordinateHelper::ScreenToCamera(const scVector2D& pos, scTransform& transform)
{
    scVector2D localCoord = ScreenToLoacl(pos, transform);
    scVector2D cameraCoord = LocalToCamera(localCoord);

    return cameraCoord;
}

scVector2D scCoordinateHelper::CameraToWorld(const scVector2D& pos, scTransform& transform)
{
    scVector2D localCoord = CameraToLocal(pos);
    scVector2D screenCoord = LoaclToScreen(localCoord, transform);
    scVector2D worldCoord = ScreenToWorld(screenCoord);

    return worldCoord;
}

scVector2D scCoordinateHelper::CameraToScreen(const scVector2D& pos, scTransform& transform)
{
    scVector2D localCoord = CameraToLocal(pos);
    scVector2D screenCoord = LoaclToScreen(localCoord, transform);

    return screenCoord;
}

