#include "scCoordinateHelper.h"

#include "scCamera.h"
#include "scTransform.h"

#include <QRect>

using namespace std;

scCoordinateHelper::scCoordinateHelper(const QRect& viewportSize)
	:mViewportSize(viewportSize)
{
}

scCoordinateHelper::~scCoordinateHelper()
{
}


// Use -1.0 * to get visibility. Do not change it to -.
scVector2D scCoordinateHelper::WorldToScreen(const scVector2D& pos)
{
    auto expr = [](double value, double size) -> double
        {
            return (value + 1.0) / 2.0 * size;
        };

    return
    {
        expr(       pos.x, static_cast<double>(mViewportSize.width())),
        expr(-1.0 * pos.y, static_cast<double>(mViewportSize.height()))
    };
}


scVector2D scCoordinateHelper::ScreenToWorld(const scVector2D& pos)
{
    auto expr = [](double value, double size) -> double
        {
            return value / size * 2.0 - 1.0;
        };

    return
    {
               expr(pos.x, static_cast<double>(mViewportSize.width())),
        -1.0 * expr(pos.y, static_cast<double>(mViewportSize.height()))
    };
}



scVector2D scCoordinateHelper::ScreenToLoacl(const scVector2D& pos, scTransform& transform)
{
    // 1. Scale
    scVector2D scaleCoord = transform.Scale(pos.x, pos.y);

    // 2. Rotate


    return scaleCoord;
}

scVector2D scCoordinateHelper::LoaclToScreen(const scVector2D& pos, scTransform& transform)
{
    // 2. Rotate
    

    // 1. Scale
    scVector2D scaleCoord = transform.UnScale(pos.x, pos.y);



    return scaleCoord;
}




scVector2D scCoordinateHelper::LocalToCamera(const scVector2D& pos)
{
    //scVector2D zoomPanCoord = mCamera->ZoomPan(x, y);

    return pos;
}

scVector2D scCoordinateHelper::CameraToLocal(const scVector2D& pos)
{
   // scVector2D zoomCoord = mCamera->UnZoomPan(x, y);

    return pos;
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

