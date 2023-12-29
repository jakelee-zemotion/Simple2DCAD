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
scVector2D scCoordinateHelper::WorldToScreen(double x, double y)
{
    auto expr = [](double value, double size) -> double
        {
            return (value + 1.0) / 2.0 * size;
        };

    return
    {
        expr(       x, static_cast<double>(mViewportSize.width())),
        expr(-1.0 * y, static_cast<double>(mViewportSize.height()))
    };
}


scVector2D scCoordinateHelper::ScreenToWorld(double x, double y)
{
    auto expr = [](double value, double size) -> double
        {
            return value / size * 2.0 - 1.0;
        };

    return
    {
               expr(x, static_cast<double>(mViewportSize.width())),
        -1.0 * expr(y, static_cast<double>(mViewportSize.height()))
    };
}



scVector2D scCoordinateHelper::ScreenToLoacl(double x, double y, scTransform& transform)
{
    // 1. Scale
    scVector2D scaleCoord = transform.Scale(x, y);

    // 2. Rotate


    return scaleCoord;
}

scVector2D scCoordinateHelper::LoaclToScreen(double x, double y, scTransform& transform)
{
    // 2. Rotate
    

    // 1. Scale
    scVector2D scaleCoord = transform.UnScale(x, y);



    return scaleCoord;
}




scVector2D scCoordinateHelper::LocalToCamera(double x, double y)
{
    //scVector2D zoomPanCoord = mCamera->ZoomPan(x, y);

    return { x, y };
}

scVector2D scCoordinateHelper::CameraToLocal(double x, double y)
{
   // scVector2D zoomCoord = mCamera->UnZoomPan(x, y);

    return { x, y };
}



scVector2D scCoordinateHelper::WorldToLocal(double x, double y, scTransform& transform)
{
    scVector2D screenCoord = WorldToScreen(x, y);
    scVector2D localCoord = ScreenToLoacl(screenCoord.x, screenCoord.y, transform);

    return localCoord;
}




scVector2D scCoordinateHelper::WorldToCamera(double x, double y, scTransform& transform)
{
    scVector2D screenCoord = WorldToScreen(x, y);
    scVector2D localCoord = ScreenToLoacl(screenCoord.x, screenCoord.y, transform);
    scVector2D cameraCoord = LocalToCamera(localCoord.x, localCoord.y);

    return cameraCoord;
}

scVector2D scCoordinateHelper::ScreenToCamera(double x, double y, scTransform& transform)
{
    scVector2D localCoord = ScreenToLoacl(x, y, transform);
    scVector2D cameraCoord = LocalToCamera(localCoord.x, localCoord.y);

    return cameraCoord;
}

scVector2D scCoordinateHelper::CameraToWorld(double x, double y, scTransform& transform)
{
    scVector2D localCoord = CameraToLocal(x, y);
    scVector2D screenCoord = LoaclToScreen(localCoord.x, localCoord.y, transform);
    scVector2D worldCoord = ScreenToWorld(screenCoord.x, screenCoord.y);

    return worldCoord;
}

scVector2D scCoordinateHelper::CameraToScreen(double x, double y, scTransform& transform)
{
    scVector2D localCoord = CameraToLocal(x, y);
    scVector2D screenCoord = LoaclToScreen(localCoord.x, localCoord.y, transform);

    return screenCoord;
}

