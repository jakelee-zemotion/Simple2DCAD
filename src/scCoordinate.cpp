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



pair<double, double> scCoordinate::ScreenToLoacl(double x, double y, scTransform& transform)
{
    // 1. Scale
    pair<double, double> scaleCoord = transform.Scale(x, y);

    // 2. Rotate


    return scaleCoord;
}

pair<double, double> scCoordinate::WorldToCamera(double x, double y, scTransform& transform)
{
    auto screenCoord = WorldToScreen(x, y);
    auto localCoord = ScreenToLoacl(screenCoord.first, screenCoord.second, transform);

    return localCoord;
}