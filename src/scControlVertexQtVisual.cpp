#include "scControlVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

scControlVertexQtVisual::scControlVertexQtVisual(
	scFaceQtVisual* face, 
	const scVector2D& pos, 
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(pos, coordinateHelper), 
		 mParentFace(face)
{
}

scControlVertexQtVisual::~scControlVertexQtVisual()
{
}



void scControlVertexQtVisual::MoveControlVertexDirectly(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x, targetMousePos.y, mVertexData->GetTransform());

	scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
		prevMousePos.x, prevMousePos.y, mVertexData->GetTransform());

	double dx = targetWorldCoord.x - prevWorldCoord.x;
	double dy = targetWorldCoord.y - prevWorldCoord.y;

	mVertexData->AddDx(dx);
	mVertexData->AddDy(dy);
}
