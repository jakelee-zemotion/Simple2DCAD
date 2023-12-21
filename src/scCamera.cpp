#include "scCamera.h"

#include <QMouseEvent>

using namespace std;

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mZoomState = ZOOM::IN;
    mZoomBackIdx = -1;
    mPanBackIdx = 0;
    mZoomCenterVector.resize(mZoomLimitSize);
    mPanDistVector.resize(mPanLimitSize);

    mPanDistVector[mPanBackIdx] = { 0.0, 0.0 };
}

scCamera::~scCamera()
{
}

void scCamera::AddPanXY(const QPointF& currentMousePos)
{
    QPointF dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    assert(mPanBackIdx >= 0 && mPanBackIdx < mPanLimitSize);

    mPanDistVector[mPanBackIdx].first += dist.x();
    mPanDistVector[mPanBackIdx].second += dist.y();

}



void scCamera::PushPopZoomCenterVector(const QPointF& currentMousePos, const ZOOM& currZoomState)
{
    if (mZoomBackIdx == -1 || mZoomState == currZoomState)
    {
        if (mZoomBackIdx + 1 >= mZoomLimitSize)
            return;

        mZoomBackIdx++; mPanBackIdx++;

        mZoomCenterVector[mZoomBackIdx] = { currentMousePos.x(), currentMousePos.y() };
        mZoomState = currZoomState;
        mPanDistVector[mPanBackIdx] = { 0.0, 0.0 };
        return;
    }

    pair<double, double> center1 = mZoomCenterVector[mZoomBackIdx];
    pair<double, double> center2 = { currentMousePos.x(), currentMousePos.y() };

    auto zoomtoPan =
        [&mZoomRatio = mZoomRatio, &currZoomState](double c1, double c2, double p1) -> double
        {
            // Zoom In
            // ((x - c1) / r + c1 + p1 - c2) * r + c2 = newX
            // newX - x = -c1 + c2 + c1 * r + p1 * r - c2 * r

            // Zoom Out
            // ((x - c1) * r + c1 + p1 - c2) / r + c2 = newX
            // newX - x = -c1 + c2 + c1 / r + p1 / r - c2 / r

            const double r = (currZoomState == ZOOM::IN ? mZoomRatio : 1.0 / mZoomRatio);
            return c2 - c1 + c1 * r - c2 * r + p1 * r;
        };


    assert(mPanBackIdx - 1 >= 0 && mPanBackIdx < mPanLimitSize);

    mPanDistVector[mPanBackIdx - 1].first += zoomtoPan(center1.first, center2.first, mPanDistVector[mPanBackIdx].first);
    mPanDistVector[mPanBackIdx - 1].second += zoomtoPan(center1.second, center2.second, mPanDistVector[mPanBackIdx].second);

    mPanBackIdx--;
    mZoomBackIdx--;
    //mZoomCenterVector.pop_back();
    //mPanDistVector.pop_back();
}


void scCamera::MultiplyDivideZoomXY(const QPointF& currentMousePos, int mouseDir)
{
    if (mouseDir > 0) // Zoom In
    {
        PushPopZoomCenterVector(currentMousePos, ZOOM::IN);
    }
    else // Zoom Out
    {
        PushPopZoomCenterVector(currentMousePos, ZOOM::OUT);
    }

}

std::pair<double, double> scCamera::Zoom(double x, double y) const
{
    assert(!mPanDistVector.empty());

    // First Panning
    x += mPanDistVector[0].first;
    y += mPanDistVector[0].second;

    for (int i = 0; i <= mZoomBackIdx; i++)
    {
        assert(i + 1 < mPanLimitSize);

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i + 1];

        // Zooming
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

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

        x += (zoomCenter.first);
        y += (zoomCenter.second);


        // Panning
        x += panDist.first;
        y += panDist.second;
    }

    qDebug() << "ZoomVector size = " << mZoomCenterVector.size() << "  //  PanVector size = " << mPanDistVector.size();

    return { x, y };
}

std::pair<double, double> scCamera::UnZoom(double x, double y) const
{
    assert(mPanBackIdx < mPanLimitSize);

    // First Panning
    x -= mPanDistVector[mPanBackIdx].first;
    y -= mPanDistVector[mPanBackIdx].second;

    for (int i = mZoomBackIdx; i >= 0; i--)
    {
        assert(i + 1 < mPanLimitSize);

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i];

        // Zooming
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

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

        x += (zoomCenter.first);
        y += (zoomCenter.second);


        // Panning
        x -= panDist.first;
        y -= panDist.second;
    }


    return { x, y };
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}