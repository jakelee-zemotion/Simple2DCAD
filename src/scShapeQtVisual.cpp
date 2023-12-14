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



std::pair<double, double> scShapeQtVisual::ScreenToTransfrom(double x, double y)
{
    // 1. Scale

    // 2. Rotate

    // 3. Translate


    return std::pair<double, double>();
}
