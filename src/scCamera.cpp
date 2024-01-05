#include "scCamera.h"

// qt
#include <QMouseEvent>

// Simple2DCAD
#include "scScene.h"

using namespace std;

scCamera::scCamera()
    :mZoomRatio(1.1)
{
    mPrevMousePos = { 0, 0 };
    
    mZoomPanMatrix = scMatrixHelper::IdentityMatrix();
    mInverseZoomPanMatrix = scMatrixHelper::IdentityMatrix();
}

scCamera::~scCamera()
{
}

void scCamera::AddPanXY(const scVector2D& currentMousePos)
{
    const scVector2D delta = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    const scMatrix2D newPanMatrix = scMatrixHelper::TranslateMatrix(delta);
    const scMatrix2D newInversePanMatrix = scMatrixHelper::InverseTranslateMatrix(delta);

    mZoomPanMatrix = (newPanMatrix * mZoomPanMatrix);
    mInverseZoomPanMatrix = (mInverseZoomPanMatrix * newInversePanMatrix);
}

void scCamera::ZoomInOut(const scVector2D& currentMousePos, int mouseDir)
{
    const scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(currentMousePos);
    const scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(currentMousePos);
    scMatrix2D scaleMatrix, inverseScaleMatrix;

    if (mouseDir > 0) // Zoom In
    {
        scaleMatrix = scMatrixHelper::ScaleMatrix({ mZoomRatio, mZoomRatio });
        inverseScaleMatrix = scMatrixHelper::InverseScaleMatrix({ mZoomRatio, mZoomRatio });

    }
    else // Zoom Out
    {
        scaleMatrix = scMatrixHelper::InverseScaleMatrix({ mZoomRatio, mZoomRatio });
        inverseScaleMatrix = scMatrixHelper::ScaleMatrix({ mZoomRatio, mZoomRatio });
    }

    const scMatrix2D nextZoomMatrix = transMatrix * scaleMatrix * inverseTransMatrix;
    const scMatrix2D nextInverseZoomMatrix = transMatrix * inverseScaleMatrix * inverseTransMatrix;

    // newM = A * oldM;
    mZoomPanMatrix = (nextZoomMatrix * mZoomPanMatrix);
    mInverseZoomPanMatrix = (mInverseZoomPanMatrix * nextInverseZoomMatrix);
}

scVector2D scCamera::ZoomPan(const scVector2D& pos) const
{
    return mZoomPanMatrix * pos;
}

scVector2D scCamera::UnZoomPan(const scVector2D& pos) const
{
    return mInverseZoomPanMatrix * pos;
}

void scCamera::SetPrevMousePos(const scVector2D& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}

double scCamera::GetZoomRatio() const
{
    return mZoomRatio;
}