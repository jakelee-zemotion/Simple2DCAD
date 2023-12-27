#include "scScaleControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleControlVertexQtVisual::scScaleControlVertexQtVisual(
	scFaceQtVisual* face,
	const QPointF& point, 
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(SHAPE_TYPE::SCALE_VERTEX, point, coordinateHelper), 
		 mParentFace(face)
{
}

scScaleControlVertexQtVisual::~scScaleControlVertexQtVisual()
{
}

void scScaleControlVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	//scVertexQtVisual::Move(targetMousePos, prevMousePos);

	/*scVector2D worldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x(), targetMousePos.y(), mVertexData->GetTransform());

	mVerticalScaleVertex.lock()->GetVertexData()->SetX(worldCoord.x);
	mHorizontalScaleVertex.lock()->GetVertexData()->SetY(worldCoord.y);


	scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetMousePos.x(), targetMousePos.y());
	scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(prevMousePos.x(), prevMousePos.y());

	double dx = targetLocalCoord.x / prevLocalCoord.x;
	double dy = targetLocalCoord.y / prevLocalCoord.y;


	scVector2D dignalWorldCoord = mCoordinateHelper->WorldToScreen(
		mDiagonalScaleVertex.lock()->GetVertexData()->GetX(), 
		mDiagonalScaleVertex.lock()->GetVertexData()->GetY());

	mParentFace->ScaleFace(dx, dy, dignalWorldCoord.x, dignalWorldCoord.y);*/
}

void scScaleControlVertexQtVisual::SetHorizontalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector)
{
	mHorizontalScaleVertex = scaleVector;
}

void scScaleControlVertexQtVisual::SetVerticalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector)
{
	mVerticalScaleVertex = scaleVector;
}

void scScaleControlVertexQtVisual::SetDiagonalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector)
{
	mDiagonalScaleVertex = scaleVector;
}

void scScaleControlVertexQtVisual::MoveControlVertexDirectly(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x(), targetMousePos.y(), mVertexData->GetTransform());

	scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
		prevMousePos.x(), prevMousePos.y(), mVertexData->GetTransform());

	double dx = targetWorldCoord.x - prevWorldCoord.x;
	double dy = targetWorldCoord.y - prevWorldCoord.y;

	mVertexData->AddDx(dx);
	mVertexData->AddDy(dy);
}