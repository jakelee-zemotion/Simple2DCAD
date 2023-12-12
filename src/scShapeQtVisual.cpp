#include "scShapeQtVisual.h"

#include <qDebug>

scShapeQtVisual::scShapeQtVisual(const QRect& viewportSize)
    :mViewportSize(viewportSize)
{
}

scShapeQtVisual::~scShapeQtVisual()
{
}


double scShapeQtVisual::ScreenToWorldX(double x)
{
    return ScreenToWorld(x, static_cast<double>(mViewportSize.width()));
}

double scShapeQtVisual::ScreenToWorldY(double y)
{
    // Use -1.0 * to get visibility. Do not change it to -.
    return -1.0 * ScreenToWorld(y, static_cast<double>(mViewportSize.height()));
}

double scShapeQtVisual::WorldToScreenX(double x)
{
    return WorldToScreen(x, static_cast<double>(mViewportSize.width()));
}

double scShapeQtVisual::WorldToScreenY(double y)
{
    // Use -1.0 * to get visibility. Do not change it to -.
    return WorldToScreen(-1.0 * y, static_cast<double>(mViewportSize.height()));
}


double scShapeQtVisual::ScreenToWorld(double value, double size)
{
    return value / size * 2.0 - 1.0;
}

double scShapeQtVisual::WorldToScreen(double value, double size)
{
    return (value + 1.0) / 2.0 * size;
}

