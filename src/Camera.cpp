#include "Camera.h"
#include "Shape.h"

Camera::Camera()
{
    mPrevMousePos = { 0, 0 };
}

Camera::~Camera()
{
}

void Camera::Pan(QVector<Shape*>& drawObjects, QVector<QPoint>& tempPoints, QPoint currentMousePos)
{
    QPoint dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    for (const auto& object : drawObjects)
    {
        for (auto& point : object->mPoints)
        {
            point += dist;
        }
    }

    for (auto& point : tempPoints)
    {
        point += dist;
    }
}

void Camera::SetPrevMousePos(QPoint prevMousePos)
{
    mPrevMousePos = prevMousePos;
}
