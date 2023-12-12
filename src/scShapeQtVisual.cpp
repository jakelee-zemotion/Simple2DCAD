#include "scShapeQtVisual.h"

#include <qDebug>

scShapeQtVisual::scShapeQtVisual(const QRect& viewportSize)
    :mViewportSize(viewportSize)
{
}

scShapeQtVisual::~scShapeQtVisual()
{
}


QPointF scShapeQtVisual::ScreenToWorld(QPointF point)
{
    return
    { 
        point.x() / static_cast<double>(mViewportSize.width()) * 2.0 - 1.0, 
        point.y() / static_cast<double>(mViewportSize.height()) * 2.0 - 1.0
    };
}

QPointF scShapeQtVisual::WorldToScreen(QPointF point)
{
    return 
    { 
        (point.x() + 1.0) / 2.0 * static_cast<double>(mViewportSize.width()),
        (point.y() + 1.0) / 2.0 * static_cast<double>(mViewportSize.height())
    };
}

