#include "scCamera.h"

#include <QMouseEvent>

using namespace std;

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mPanX = 0.0;
    mPanY = 0.0;

    mZoomCenterVector.reserve(mZoomLimit);
    mZoomState = ZOOM::IN;
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
    if (mouseDir > 0) // Zoom In
    {
        if (mZoomCenterVector.empty() || mZoomState == ZOOM::IN)
        {
            if (mZoomCenterVector.size() >= mZoomLimit)
                return;

            mZoomCenterVector.push_back({ currentMousePos.x(), currentMousePos.y() });
            mZoomState = ZOOM::IN;
            return;
        }

        pair<double, double> center1 = mZoomCenterVector.back();
        pair<double, double> center2 = { currentMousePos.x(), currentMousePos.y()};

        auto zoomtoPan = 
            [&mZoomRatio = mZoomRatio](double c1, double c2) -> double
            {
                const double r = mZoomRatio;

                // ((x - c1) / r + c1 - c2) * r + c2 = newX
                // newX - x = -c1 + c2 + c1 * r - c2 * r
                return c2 - c1 + c1 * r - c2 * r;
            };

        mPanX += zoomtoPan(center1.first, center2.first);
        mPanY += zoomtoPan(center1.second, center2.second);

        mZoomCenterVector.pop_back();
    }
    else // Zoom Out
    {
        if (mZoomCenterVector.empty() || mZoomState == ZOOM::OUT)
        {
            if (mZoomCenterVector.size() >= mZoomLimit)
                return;

            mZoomCenterVector.push_back({ currentMousePos.x(), currentMousePos.y() });
            mZoomState = ZOOM::OUT;
            return;
        }

        pair<double, double> center1 = mZoomCenterVector.back();
        pair<double, double> center2 = { currentMousePos.x(), currentMousePos.y() };

        auto zoomtoPan =
            [&mZoomRatio = mZoomRatio](double c1, double c2) -> double
            {
                const double r = mZoomRatio;

                // ((x - c1) * r + c1 - c2) / r + c2 = newX
                // newX - x = -c1 + c2 + c1 / r - c2 / r
                return c2 - c1 + c1 / r - c2 / r;
            };

        mPanX += zoomtoPan(center1.first, center2.first);
        mPanY += zoomtoPan(center1.second, center2.second);

        mZoomCenterVector.pop_back();
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
    for (const auto& zoomCenter : mZoomCenterVector)
    {
        x -= (zoomCenter.first - mPanX);
        y -= (zoomCenter.second - mPanY);

        if (mZoomState == ZOOM::IN)
        {
            x *= mZoomRatio;
            y *= mZoomRatio;
        }
        else
        {
            x /= mZoomRatio;
            y /= mZoomRatio;
        }

        x += (zoomCenter.first  - mPanX);
        y += (zoomCenter.second - mPanY);
    }

    qDebug() << "ZoomVector size = " << mZoomCenterVector.size();

    return { x, y };
}

std::pair<double, double> scCamera::UnZoom(double x, double y) const
{
    for (auto iter = mZoomCenterVector.rbegin(); iter != mZoomCenterVector.rend(); iter++)
    {
        const auto& zoomCenter = *iter;

        x -= (zoomCenter.first - mPanX);
        y -= (zoomCenter.second - mPanY);

        if (mZoomState == ZOOM::IN)
        {
            x /= mZoomRatio;
            y /= mZoomRatio;
        }
        else
        {
            x *= mZoomRatio;
            y *= mZoomRatio;
        }

        x += (zoomCenter.first - mPanX);
        y += (zoomCenter.second - mPanY);
    }


    return { x, y };
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}
