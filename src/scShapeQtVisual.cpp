#include "scShapeQtVisual.h"

#include <qDebug>

using namespace std;

scShapeQtVisual::scShapeQtVisual(const QRect& viewportSize)
    :mViewportSize(viewportSize)
{
}

scShapeQtVisual::~scShapeQtVisual()
{
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

double scShapeQtVisual::ScreenToWorldExpression(double value, double size)
{
    return value / size * 2.0 - 1.0;
}

double scShapeQtVisual::WorldToScreenExpression(double value, double size)
{
    return (value + 1.0) / 2.0 * size;
}

