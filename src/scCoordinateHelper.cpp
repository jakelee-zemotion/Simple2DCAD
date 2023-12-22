#include "scCoordinateHelper.h"

#include "scCamera.h"
#include "scTransform.h"

#include <QRect>

using namespace std;

scCoordinateHelper::scCoordinateHelper(scCamera& camera, const QRect& viewportSize)
	:mCamera(camera), mViewportSize(viewportSize)
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
        expr(x, static_cast<double>(mViewportSize.width())),
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




std::pair<double, double> scCoordinateHelper::LocalToCamera(double x, double y)
{
    // Pan Zoom Pan Zoom Pan ...
    auto zoomPanCoord = mCamera.ZoomPan(x, y);

    return zoomPanCoord;
}

std::pair<double, double> scCoordinateHelper::CameraToLocal(double x, double y)
{
    // UnPan UnZoom UnPan UnZoom UnPan ...
    auto zoomCoord = mCamera.UnZoomPan(x, y);

    return zoomCoord;
}




scVector2D scCoordinateHelper::WorldToCamera(double x, double y, scTransform& transform)
{
    scVector2D screenCoord = WorldToScreen(x, y);
    scVector2D localCoord = ScreenToLoacl(screenCoord.x, screenCoord.y, transform);
    auto cameraCoord = LocalToCamera(localCoord.x, localCoord.y);

    return { cameraCoord.first, cameraCoord.second };
}

scVector2D scCoordinateHelper::CameraToWorld(double x, double y, scTransform& transform)
{
    auto localCoord = CameraToLocal(x, y);
    scVector2D screenCoord = LoaclToScreen(localCoord.first, localCoord.second, transform);
    scVector2D worldCoord = ScreenToWorld(screenCoord.x, screenCoord.y);

    return worldCoord;
}

