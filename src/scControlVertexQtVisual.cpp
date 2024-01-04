#include "scControlVertexQtVisual.h"

// Simple2DCAD
#include "scCoordinateHelper.h"
#include "scVertexData.h"

scControlVertexQtVisual::scControlVertexQtVisual(scFaceQtVisual* face, const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scVertexQtVisual(pos, coordinateHelper), mParentFace(face)
{
}

scControlVertexQtVisual::~scControlVertexQtVisual()
{
}

void scControlVertexQtVisual::MultiplyRotateXY(double angle, double transX, double transY)
{
	mVertexData->GetTransform().MultiplyRotateXY(angle, transX, transY);
}

void scControlVertexQtVisual::MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY, double angle)
{
	mVertexData->GetTransform().MultiplyScaleXY(scaleX, scaleY, transX, transY, angle);
}

scVector2D scControlVertexQtVisual::GetLocalXY() const
{
	scVector2D localCoord = mCoordinateHelper->WorldToLocal(mVertexData->GetPos(), mVertexData->GetTransform());
	return localCoord;
}
