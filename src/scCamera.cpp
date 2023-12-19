#include "scCamera.h"

#include <QMouseEvent>

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mPanX = 0.0;
    mPanY = 0.0;
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
    /*if (mouseDir > 0)
    {
        mZoomX *= mZoomRatio;
        mZoomY *= mZoomRatio;
    }
    else
    {
        mZoomX /= mZoomRatio;
        mZoomY /= mZoomRatio;
    }*/


    /*if (mouseDir < 0)
    {
        auto m = mZoomDataList.back();
        mZoomDataList.pop_back();

        return;
    }*/

    mZoomDataList.push_back({ currentMousePos.x(), currentMousePos.y(), mouseDir });

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
    for (const auto& zoom : mZoomDataList)
    {
        x -= (zoom.centerX - mPanX);
        y -= (zoom.centerY - mPanY);

        if (zoom.mouseDir > 0)
        {
            x *= mZoomRatio;
            y *= mZoomRatio;
        }
        else
        {
            x /= mZoomRatio;
            y /= mZoomRatio;
        }

        x += (zoom.centerX - mPanX);
        y += (zoom.centerY - mPanY);
    }

    qDebug() << "ZoomList size = " << mZoomDataList.size();

    return { x, y };
}

std::pair<double, double> scCamera::UnZoom(double x, double y) const
{
    for (auto iter = mZoomDataList.rbegin(); iter != mZoomDataList.rend(); iter++)
    {
        const auto& zoom = *iter;

        x -= (zoom.centerX - mPanX);
        y -= (zoom.centerY - mPanY);

        if (zoom.mouseDir > 0)
        {
            x /= mZoomRatio;
            y /= mZoomRatio;
        }
        else
        {
            x *= mZoomRatio;
            y *= mZoomRatio;
        }

        x += (zoom.centerX - mPanX);
        y += (zoom.centerY - mPanY);
    }


    return { x, y };
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}
