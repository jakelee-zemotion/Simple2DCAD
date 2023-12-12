#include "scCamera.h"

#include <QMouseEvent>

scCamera::scCamera()
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

   /* for (const auto& object : mScene.mScene)
    {
        for (auto& point : object->mPoints)
        {
            point += dist;
        }
    }*/
}

void scCamera::Zoom(QPoint currentMousePos, int mouseDir)
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

void scCamera::SetPrevMousePos(QPoint prevMousePos)
{
    mPrevMousePos = prevMousePos;
}