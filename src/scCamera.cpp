#include "scCamera.h"

#include <QMouseEvent>

using namespace std;

scCamera::scCamera()
{
    mPrevMousePos = { 0, 0 };

    mPrevZoomState = ZOOM::IN;
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



void scCamera::AddRemoveZoomPanVectorElement(const QPointF& currentMousePos, const ZOOM& currZoomState)
{
    // Zoom/Pan information is saved in vectors step by step.
    // 
    // If the vector is empty or 
    // the previous state is the same as the current state (e.g. Zoom In->In->In, Out->Out->Out)
    if (mZoomBackIdx == -1 || mPrevZoomState == currZoomState)
    {
        // Add Zoom/Pan Elements.
        if (mZoomBackIdx + 1 >= mZoomLimitSize)
            return;

        mZoomBackIdx++; mPanBackIdx++;

        mZoomCenterVector[mZoomBackIdx] = { currentMousePos.x(), currentMousePos.y() };
        mPrevZoomState = currZoomState;
        mPanDistVector[mPanBackIdx] = { 0.0, 0.0 };
        return;
    }

    // Remove Zoom/Pan Elements.
    // ####################################
    // Consider the case of 
    // [stage1] --ZoomIn --> [stage2] --ZoomOut--> [stage3]
    // or
    // [stage1] --ZoomOut--> [stage2] --ZoomIn --> [stage3]
    // 
    // Here, the object size of stage3 is the same as stage1. 
    // 
    // This is because the Zoom ratio for all Zoom steps is the same. (mZoomRatio)
    // 
    // So instead of going through the steps above, 
    // we just find the distance difference between steps 1 and 3 
    // and add it to Pan.
    // ####################################

    pair<double, double> center1 = mZoomCenterVector[mZoomBackIdx];
    pair<double, double> center2 = { currentMousePos.x(), currentMousePos.y() };

    // Find the distance difference between steps 1 and 3.
    auto zoomtoPan =
        [&mZoomRatio = mZoomRatio, &currZoomState](double c1, double c2, double p1) -> double
        {
            // ####################################
            // 1. [stage1] --ZoomOut--> [stage2] --ZoomIn --> [stage3]
            // 
            // ((x - c1) / r + c1 + p1 - c2) * r + c2 = newX
            // newX - x = -c1 + c2 + c1 * r + p1 * r - c2 * r
            //
            //
            // 2. [stage1] --ZoomIn --> [stage2] --ZoomOut--> [stage3]
            // 
            // ((x - c1) * r + c1 + p1 - c2) / r + c2 = newX
            // newX - x = -c1 + c2 + c1 / r + p1 / r - c2 / r
            //  
            // (c.f. newX - x = distance)
            // ####################################

            const double r = (currZoomState == ZOOM::IN ? mZoomRatio : 1.0 / mZoomRatio);
            return c2 - c1 + c1 * r - c2 * r + p1 * r;
        };


    assert(mPanBackIdx - 1 >= 0 && mPanBackIdx < mPanLimitSize);

    // Add the distance to Pan.
    mPanDistVector[mPanBackIdx - 1].first += zoomtoPan(center1.first, center2.first, mPanDistVector[mPanBackIdx].first);
    mPanDistVector[mPanBackIdx - 1].second += zoomtoPan(center1.second, center2.second, mPanDistVector[mPanBackIdx].second);

    mPanBackIdx--;
    mZoomBackIdx--;
}


void scCamera::ZoomInOut(const QPointF& currentMousePos, int mouseDir)
{
    if (mouseDir > 0) // Zoom In
    {
        AddRemoveZoomPanVectorElement(currentMousePos, ZOOM::IN);
    }
    else // Zoom Out
    {
        AddRemoveZoomPanVectorElement(currentMousePos, ZOOM::OUT);
    }

}

scVector2D scCamera::ZoomPan(double x, double y) const
{
    assert(!mPanDistVector.empty());

    // Pan Zoom Pan Zoom Pan ...
    // First Pan
    x += mPanDistVector[0].first;
    y += mPanDistVector[0].second;

    for (int i = 0; i <= mZoomBackIdx; i++)
    {
        assert(i + 1 < mPanLimitSize);

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i + 1];

        // Zoom
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

        if (mPrevZoomState == ZOOM::IN)
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


        // Pan
        x += panDist.first;
        y += panDist.second;
    }

    //qDebug() << "ZoomVector size = " << mZoomCenterVector.size() << "  //  PanVector size = " << mPanDistVector.size();

    return { x, y };
}

scVector2D scCamera::UnZoomPan(double x, double y) const
{
    assert(mPanBackIdx < mPanLimitSize);

    // UnPan UnZoom UnPan UnZoom UnPan ...
    // First UnPan
    x -= mPanDistVector[mPanBackIdx].first;
    y -= mPanDistVector[mPanBackIdx].second;

    for (int i = mZoomBackIdx; i >= 0; i--)
    {
        assert(i + 1 < mPanLimitSize);

        const auto& zoomCenter = mZoomCenterVector[i];
        const auto& panDist = mPanDistVector[i];

        // UnZoom
        x -= (zoomCenter.first);
        y -= (zoomCenter.second);

        if (mPrevZoomState == ZOOM::IN)
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


        // UnPan
        x -= panDist.first;
        y -= panDist.second;
    }


    return { x, y };
}

void scCamera::SetPrevMousePos(const QPointF& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}