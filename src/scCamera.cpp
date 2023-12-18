#include "scCamera.h"

#include <QMouseEvent>

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mPanX = 0.0;
    mPanY = 0.0;

    mZoomX = 1.0;
    mZoomY = 1.0;
}

scCamera::~scCamera()
{
}

void scCamera::AddPanXY(const QPointF& currentMousePos)
{
    QPointF dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    mPanX += dist.x();
    mPanY += dist.y();

   /* for (const auto& object : mScene.mScene)
    {
        for (auto& point : object->mPoints)
        {
            point += dist;
        }
    }*/
}

void scCamera::MultiplyZoomXY(const QPointF& currentMousePos, int mouseDir)
{
    /*for (const auto& object : mScene.mScene)
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
    }*/
    
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}

double scCamera::GetPanX() const
{
    return mPanX;
}

double scCamera::GetPanY() const
{
    return mPanY;
}
