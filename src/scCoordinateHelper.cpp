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
pair<double, double> scCoordinateHelper::WorldToScreen(double x, double y)
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


pair<double, double> scCoordinateHelper::ScreenToWorld(double x, double y)
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



pair<double, double> scCoordinateHelper::ScreenToLoacl(double x, double y, scTransform& transform)
{
    // 1. Scale
    auto scaleCoord = transform.Scale(x, y);

    // 2. Rotate


    return scaleCoord;
}

std::pair<double, double> scCoordinateHelper::LoaclToScreen(double x, double y, scTransform& transform)
{
    // 2. Rotate
    

    // 1. Scale
    auto scaleCoord = transform.UnScale(x, y);



    return scaleCoord;
}




std::pair<double, double> scCoordinateHelper::LocalToCamera(double x, double y)
{
    // 1. Zoom
    auto zoomCoord = mCamera.Zoom(x, y);

    //// 2. Pan
    //auto panCoord = mCamera.Pan(zoomCoord.first, zoomCoord.second);

    return zoomCoord;
}

std::pair<double, double> scCoordinateHelper::CameraToLocal(double x, double y)
{
    //// 1. Pan
    //auto panCoord = mCamera.UnPan(x, y);

    // 2. Zoom
    auto zoomCoord = mCamera.UnZoom(x, y);

    return zoomCoord;
}




pair<double, double> scCoordinateHelper::WorldToCamera(double x, double y, scTransform& transform)
{
    auto screenCoord = WorldToScreen(x, y);
    auto localCoord = ScreenToLoacl(screenCoord.first, screenCoord.second, transform);
    auto cameraCoord = LocalToCamera(localCoord.first, localCoord.second);

    return cameraCoord;
}

std::pair<double, double> scCoordinateHelper::CameraToWorld(double x, double y, scTransform& transform)
{
    auto localCoord = CameraToLocal(x, y);
    auto screenCoord = LoaclToScreen(localCoord.first, localCoord.second, transform);
    auto worldCoord = ScreenToWorld(screenCoord.first, screenCoord.second);

    return worldCoord;
}

