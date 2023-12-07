#include "scCamera.h"
#include "scShape.h"

#include <QMouseEvent>

scCamera::scCamera(scShapeVector& shapeObjects, QPoint viewportSize)
    :mShapeObjects(shapeObjects), mViewportSize(viewportSize)
{
    mPrevMousePos = { 0, 0 };
}

scCamera::~scCamera()
{
}

void scCamera::Pan(QPoint currentMousePos)
{
    QPoint dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    for (const auto& object : mShapeObjects.mShapes)
    {
        for (auto& point : object->mPoints)
        {
            point += dist;
        }
    }
}

void scCamera::Zoom(QPoint currentMousePos, int mouseDir)
{
    for (const auto& object : mShapeObjects.mShapes)
    {
        for (auto& point : object->mPoints)
        {
            point -= currentMousePos;
            if (mouseDir > 0)
            {
                point *= zoomValue;
            }
            else
            {
                point /= zoomValue;
            }
            point += currentMousePos;
        }
    }
    
}

void scCamera::SetPrevMousePos(QPoint prevMousePos)
{
    mPrevMousePos = prevMousePos;
}


// The ones below are not used.
QPoint scCamera::ScreenToWorld(QPoint point)
{
    return { point.x() / mViewportSize.x() * 2 - 1, point.y() / mViewportSize.y() * 2 - 1 };
}

QPoint scCamera::WorldToScreen(QPoint point)
{
    return { (point.x() + 1) / 2 * mViewportSize.x(), (point.y() + 1) / 2 * mViewportSize.y() };
}
