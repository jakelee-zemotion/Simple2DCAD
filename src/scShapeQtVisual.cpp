#include "scShapeQtVisual.h"

#include <qDebug>

using namespace std;

scShapeQtVisual::scShapeQtVisual(SHAPE_TYPE shapeType, const QRect& viewportSize)
    : mShapeType(shapeType), mViewportSize(viewportSize), mHitSize(10.0)
{
    mShapeColorType = COLOR_TYPE::DEFAULT;
    mShapeColors = vector<Qt::GlobalColor>(3, Qt::black);
}

scShapeQtVisual::~scShapeQtVisual()
{
}

void scShapeQtVisual::SetShapeColorType(const COLOR_TYPE color)
{
    mShapeColorType = color;
}

SHAPE_TYPE scShapeQtVisual::GetShapeType() const
{
    return mShapeType;
}

scShapeID scShapeQtVisual::GetID() const
{
    return mShapeID;
}

// Use -1.0 * to get visibility. Do not change it to -.
pair<double, double> scShapeQtVisual::ScreenToWorld(double x, double y)
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

pair<double, double> scShapeQtVisual::WorldToScreen(double x, double y)
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



pair<double, double> scShapeQtVisual::ScreenToLoacl(double x, double y, scTransform& transform)
{
    // 1. Scale
    pair<double, double> scaleCoord = transform.Scale(x, y);

    // 2. Rotate


    return scaleCoord;
}

pair<double, double> scShapeQtVisual::WorldToCamera(double x, double y, scTransform& transform)
{
    auto screenCoord = WorldToScreen(x, y);
    auto localCoord = ScreenToLoacl(screenCoord.first, screenCoord.second, transform);

    return localCoord;
}