#include "scCamera.h"

#include <QMouseEvent>

using namespace std;

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mZoomCenterVector.reserve(mZoomLimit);
    mZoomState = ZOOM::IN;

    idx = 0;
    mPanDistVector.push_back({ 0.0, 0.0 });
}

scCamera::~scCamera()
{
}

void scCamera::AddPanXY(const QPointF& currentMousePos)
{
    QPointF dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    mPanDistVector[idx].first += dist.x();
    mPanDistVector[idx].second += dist.y();

}



void scCamera::PushPopZoomCenterVector(const QPointF& currentMousePos, const ZOOM& currZoomState)
{
    //if (mZoomCenterVector.empty() || mZoomState == currZoomState)
    //{
    //    if (mZoomCenterVector.size() >= mZoomLimit)
    //        return;

    //    mZoomCenterVector.push_back({ currentMousePos.x(), currentMousePos.y() });
    //    mZoomState = currZoomState;
    //    return;
    //}

    //pair<double, double> center1 = mZoomCenterVector.back();
    //pair<double, double> center2 = { currentMousePos.x(), currentMousePos.y() };

    //auto zoomtoPan =
    //    [&mZoomRatio = mZoomRatio, &currZoomState](double c1, double c2) -> double
    //    {
    //        // Zoom In
    //        // ((x - c1) / r + c1 - c2) * r + c2 = newX
    //        // newX - x = -c1 + c2 + c1 * r - c2 * r

    //        // Zoom Out
    //        // ((x - c1) * r + c1 - c2) / r + c2 = newX
    //        // newX - x = -c1 + c2 + c1 / r - c2 / r

    //        const double r = (currZoomState == ZOOM::IN ? mZoomRatio : 1.0 / mZoomRatio);
    //        return c2 - c1 + c1 * r - c2 * r;
    //    };

    ////mPanX += zoomtoPan(center1.first, center2.first);
    ////mPanY += zoomtoPan(center1.second, center2.second);

    //mZoomCenterVector.pop_back();
}


void scCamera::MultiplyDivideZoomXY(const QPointF& currentMousePos, int mouseDir)
{
    if (mouseDir > 0) // Zoom In
    {
        mZoomCenterVector.push_back({ currentMousePos.x(), currentMousePos.y() });
        mPanDistVector.push_back({ 0.0, 0.0 });
        mZoomStates.push_back(ZOOM::IN);

        idx++;
        //PushPopZoomCenterVector(currentMousePos, ZOOM::IN);
    }
    else // Zoom Out
    {
        mZoomCenterVector.push_back({ currentMousePos.x(), currentMousePos.y()});
        mPanDistVector.push_back({ 0.0, 0.0 });
        mZoomStates.push_back(ZOOM::OUT);

        idx++;
       // PushPopZoomCenterVector(currentMousePos, ZOOM::OUT);
    }

}

//std::pair<double, double> scCamera::Pan(double x, double y) const
//{
//    x += mPanX;
//    y += mPanY;
//
//    return { x, y };
//}
//
//std::pair<double, double> scCamera::UnPan(double x, double y) const
//{
//    x -= mPanX;
//    y -= mPanY;
//
//    return { x, y };
//}

std::pair<double, double> scCamera::Zoom(double x, double y) const
{
    assert(!mPanDistVector.empty());

    // First Panning
    x += mPanDistVector[0].first;
    y += mPanDistVector[0].second;

    for (int i = 0; i < mZoomCenterVector.size(); i++)
    {
        assert(i + 1 < mPanDistVector.size());

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i + 1];

        // Zooming
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

        if (mZoomStates[i] == ZOOM::IN)
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

    qDebug() << "ZoomVector size = " << mZoomCenterVector.size();

    return { x, y };
}

std::pair<double, double> scCamera::UnZoom(double x, double y) const
{
    assert(!mPanDistVector.empty());

    // First Panning
    x -= mPanDistVector.back().first;
    y -= mPanDistVector.back().second;

    for (int i = mZoomCenterVector.size() - 1; i >= 0; i--)
    {
        assert(i < mPanDistVector.size());

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i];

        // Zooming
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

        if (mZoomStates[i] == ZOOM::IN)
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