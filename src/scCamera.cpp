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

}

void scCamera::MultiplyDivideZoomXY(const QPointF& currentMousePos, int mouseDir)
{
    if (mouseDir > 0)
    {
        mZoomX *= mZoomRatio;
        mZoomY *= mZoomRatio;
    }
    else
    {
        mZoomX /= mZoomRatio;
        mZoomY /= mZoomRatio;
    }
}

std::pair<double, double> scCamera::Pan(double x, double y) const
{
    x += mPanX;
    y += mPanY;

    return { x, y };
}

std::pair<double, double> scCamera::UnPan(double x, double y) const
{
    x -= mPanX;
    y -= mPanY;

    return { x, y };
}

std::pair<double, double> scCamera::Zoom(double x, double y) const
{
    x *= mZoomX;
    y *= mZoomY;

    return { x, y };
}

std::pair<double, double> scCamera::UnZoom(double x, double y) const
{
    x /= mZoomX;
    y /= mZoomY;

    return { x, y };
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}
