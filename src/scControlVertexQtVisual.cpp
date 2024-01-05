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

void scControlVertexQtVisual::MultiplyRotateXY(const scVector2D& trans, const double angle)
{
	mVertexData->GetTransform().MultiplyRotateXY(trans, angle);
}

void scControlVertexQtVisual::MultiplyScaleXY(const scVector2D& scale, const scVector2D& trans, const double angle)
{
	mVertexData->GetTransform().MultiplyScaleXY(scale, trans, angle);
}

scVector2D scControlVertexQtVisual::GetLocalXY() const
{
	scVector2D localCoord = mCoordinateHelper->WorldToLocal(mVertexData->GetPos(), mVertexData->GetTransform());
	return localCoord;
}
