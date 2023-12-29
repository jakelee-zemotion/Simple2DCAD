#include "scCamera.h"
#include "scScene.h"

#include <QMouseEvent>

using namespace std;

scCamera::scCamera(const std::shared_ptr<scScene>& scene)
    :mScene(scene)
{
    mPrevMousePos = { 0, 0 };
    
    mZoomPanMatrix = MatrixHelper::IdentityMatrix();
    mInverseZoomPanMatrix = MatrixHelper::IdentityMatrix();
}

scCamera::~scCamera()
{
}

void scCamera::AddPanXY(const scVector2D& currentMousePos)
{

    mScene->MoveVertices(currentMousePos, mPrevMousePos);


    scVector2D dist = currentMousePos - mPrevMousePos;
    mPrevMousePos = currentMousePos;

    scMatrix2D newPanMatrix = MatrixHelper::TranslateMatrix(dist.x, dist.y);
    scMatrix2D newInversePanMatrix = MatrixHelper::InverseTranslateMatrix(dist.x, dist.y);

    mZoomPanMatrix = (newPanMatrix * mZoomPanMatrix);
    mInverseZoomPanMatrix = (mInverseZoomPanMatrix * newInversePanMatrix);
}


void scCamera::ZoomInOut(const scVector2D& currentMousePos, int mouseDir)
{
    scMatrix2D inverseTransMatrix = MatrixHelper::InverseTranslateMatrix(currentMousePos.x, currentMousePos.y);
    scMatrix2D scaleMatrix, inverseScaleMatrix;
    scMatrix2D transMatrix = MatrixHelper::TranslateMatrix(currentMousePos.x, currentMousePos.y);

    if (mouseDir > 0) // Zoom In
    {
        scaleMatrix = MatrixHelper::ScaleMatrix(mZoomRatio, mZoomRatio);
        inverseScaleMatrix = MatrixHelper::InverseScaleMatrix(mZoomRatio, mZoomRatio);

    }
    else // Zoom Out
    {
        scaleMatrix = MatrixHelper::InverseScaleMatrix(mZoomRatio, mZoomRatio);
        inverseScaleMatrix = MatrixHelper::ScaleMatrix(mZoomRatio, mZoomRatio);
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