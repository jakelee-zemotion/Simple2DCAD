#include "scCoordinate.h"

using namespace std;

scCoordinate::scCoordinate(const scCamera& camera, const QRect& viewportSize)
	:mCamera(camera), mViewportSize(viewportSize)
{
}

scCoordinate::~scCoordinate()
{
}


// Use -1.0 * to get visibility. Do not change it to -.
pair<double, double> scCoordinate::WorldToScreen(double x, double y)
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


pair<double, double> scCoordinate::ScreenToWorld(double x, double y)
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



pair<double, double> scCoordinate::ScreenToLoacl(double x, double y, scTransform& transform)
{
    // 1. Scale
    pair<double, double> scaleCoord = transform.Scale(x, y);

    // 2. Rotate


    return scaleCoord;
}

std::pair<double, double> scCoordinate::LoaclToScreen(double x, double y, scTransform& transform)
{
    // 2. Rotate
    // 
    // 1. Scale
    pair<double, double> scaleCoord = transform.UnScale(x, y);



    return scaleCoord;
}




std::pair<double, double> scCoordinate::LocalToCamera(double x, double y)
{
    x += mCamera.GetPanX();
    y += mCamera.GetPanY();

    return { x, y };
}

std::pair<double, double> scCoordinate::CameraToLocal(double x, double y)
{
    x -= mCamera.GetPanX();
    y -= mCamera.GetPanY();

    return { x, y };
}




pair<double, double> scCoordinate::WorldToCamera(double x, double y, scTransform& transform)
{
    auto screenCoord = WorldToScreen(x, y);
    auto localCoord = ScreenToLoacl(screenCoord.first, screenCoord.second, transform);
    auto cameraCoord = LocalToCamera(localCoord.first, localCoord.second);

    return cameraCoord;
}

std::pair<double, double> scCoordinate::CameraToWorld(double x, double y, scTransform& transform)
{
    auto localCoord = CameraToLocal(x, y);
    auto screenCoord = LoaclToScreen(localCoord.first, localCoord.second, transform);
    auto worldCoord = ScreenToWorld(screenCoord.first, screenCoord.second);

    return worldCoord;
}

