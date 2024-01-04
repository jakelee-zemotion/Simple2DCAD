#include "scCamera.h"

// qt
#include <QMouseEvent>

// Simple2DCAD
#include "scScene.h"

using namespace std;

scCamera::scCamera()
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

    //mScene->MoveVertices(currentMousePos, mPrevMousePos);


    scVector2D dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    scMatrix2D newPanMatrix = scMatrixHelper::TranslateMatrix(dist.x, dist.y);
    scMatrix2D newInversePanMatrix = scMatrixHelper::InverseTranslateMatrix(dist.x, dist.y);

    mZoomPanMatrix = (newPanMatrix * mZoomPanMatrix);
    mInverseZoomPanMatrix = (mInverseZoomPanMatrix * newInversePanMatrix);
}


void scCamera::ZoomInOut(const scVector2D& currentMousePos, int mouseDir)
{
    scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(currentMousePos.x, currentMousePos.y);
    scMatrix2D scaleMatrix, inverseScaleMatrix;
    scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(currentMousePos.x, currentMousePos.y);

    if (mouseDir > 0) // Zoom In
    {
        scaleMatrix = scMatrixHelper::ScaleMatrix(mZoomRatio, mZoomRatio);
        inverseScaleMatrix = scMatrixHelper::InverseScaleMatrix(mZoomRatio, mZoomRatio);
        mZoomOutCount--;

    }
    else // Zoom Out
    {
        scaleMatrix = scMatrixHelper::InverseScaleMatrix(mZoomRatio, mZoomRatio);
        inverseScaleMatrix = scMatrixHelper::ScaleMatrix(mZoomRatio, mZoomRatio);
        mZoomOutCount++;
    }


    scMatrix2D nextZoomMatrix = transMatrix * scaleMatrix * inverseTransMatrix;
    scMatrix2D nextInverseZoomMatrix = transMatrix * inverseScaleMatrix * inverseTransMatrix;

    // newM = A * oldM;
    mZoomPanMatrix = (nextZoomMatrix * mZoomPanMatrix);
    mInverseZoomPanMatrix = (mInverseZoomPanMatrix * nextInverseZoomMatrix);
}

scVector2D scCamera::ZoomPan(double x, double y) const
{
    scVector2D v = { x, y };
    scVector2D result = mZoomPanMatrix * v;

    return result;
}

scVector2D scCamera::UnZoomPan(double x, double y) const
{
    scVector2D v = { x, y };
    scVector2D result = mInverseZoomPanMatrix * v;

    return result;
}

void scCamera::SetPrevMousePos(const scVector2D& prevMousePos)
{
    mPrevMousePos = prevMousePos;
}

double scCamera::GetZoomRatio() const
{
    return mZoomRatio;
}

bool scCamera::CanZoomIn() const
{
    return mZoomOutCount > mZoomOutCountMinLimit;
}

bool scCamera::CanZoomOut() const
{
    return mZoomOutCount < mZoomOutCountMaxLimit;
}
