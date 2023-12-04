#include "Camera.h"
#include "Shape.h"

#include <QMouseEvent>

Camera::Camera(QVector<Shape*>& drawObjects, QVector<QPoint>& tempPoints, QPoint viewportSize)
    :mDrawObjects(drawObjects), mTempPoints(tempPoints), mViewportSize(viewportSize)
{
    mPrevMousePos = { 0, 0 };
}

Camera::~Camera()
{
}

void Camera::Pan(QMouseEvent* event, QPoint currentMousePos)
{
    if (event->buttons() != Qt::MiddleButton)
        return;
    
    QPoint dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    for (const auto& object : mDrawObjects)
    {
        for (auto& point : object->mPoints)
        {
            point += dist;
        }
    }

    for (auto& point : mTempPoints)
    {
        point += dist;
    }
}

void Camera::Zoom(QWheelEvent* event, bool isCtrlPressed, QPoint currentMousePos)
{
    if (!isCtrlPressed)
        return;

    int dir = event->angleDelta().y();

    for (const auto& object : mDrawObjects)
    {
        for (auto& point : object->mPoints)
        {
            point -= currentMousePos;
            if (dir > 0)
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

    for (auto& point : mTempPoints)
    {
        point -= currentMousePos;
        if (dir > 0)
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

void Camera::SetPrevMousePos(QMouseEvent* event, QPoint prevMousePos)
{
    if (event->buttons() != Qt::MiddleButton)
        return;
    
    mPrevMousePos = prevMousePos;
}

QPoint Camera::ScreenToWorld(QPoint point)
{
    return { point.x() / mViewportSize.x() * 2 - 1, point.y() / mViewportSize.y() * 2 - 1 };
}

QPoint Camera::WorldToScreen(QPoint point)
{
    return { (point.x() + 1) / 2 * mViewportSize.x(), (point.y() + 1) / 2 * mViewportSize.y() };
}
