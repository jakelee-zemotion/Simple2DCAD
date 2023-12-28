#include "scScaleControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleControlVertexQtVisual::scScaleControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& point,
	const BOX_POSITION& boxPos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(point, coordinateHelper), 
		 mParentFace(face), mBoxPos(boxPos)
{
	mShapeType = SHAPE_TYPE::SCALE_VERTEX;
}

scScaleControlVertexQtVisual::~scScaleControlVertexQtVisual()
{
}

void scScaleControlVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	mParentFace->ScaleFace(targetMousePos, prevMousePos, mBoxPos);
}

void scScaleControlVertexQtVisual::MoveControlVertexDirectly(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
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