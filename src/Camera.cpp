#include "Camera.h"
#include "Shape.h"

#include <QMouseEvent>

Camera::Camera(ShapeVector& shapeObjects, QVector<QPoint>& tempPoints, QPoint viewportSize)
    :mShapeObjects(shapeObjects), mTempPoints(tempPoints), mViewportSize(viewportSize)
{
    mPrevMousePos = { 0, 0 };
}

Camera::~Camera()
{
}

void Camera::Pan(QPoint currentMousePos)
{
    QPoint dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    for (const auto& object : mShapeObjects)
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

void Camera::Zoom(QPoint currentMousePos, int mouseDir)
{
    for (const auto& object : mShapeObjects)
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

    for (auto& point : mTempPoints)
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

void Camera::SetPrevMousePos(QPoint prevMousePos)
{
    mPrevMousePos = prevMousePos;
}


// The ones below are not used.
QPoint Camera::ScreenToWorld(QPoint point)
{
    return { point.x() / mViewportSize.x() * 2 - 1, point.y() / mViewportSize.y() * 2 - 1 };
}

QPoint Camera::WorldToScreen(QPoint point)
{
    return { (point.x() + 1) / 2 * mViewportSize.x(), (point.y() + 1) / 2 * mViewportSize.y() };
}
