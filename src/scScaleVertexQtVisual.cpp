#include "scScaleVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleVertexQtVisual::scScaleVertexQtVisual(
	const shared_ptr<scFaceQtVisual>& face,
	const QPointF& point, 
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(SHAPE_TYPE::SCALE_VERTEX, point, coordinateHelper), 
		 mParentFace(face)
{
}

scScaleVertexQtVisual::~scScaleVertexQtVisual()
{
}

void scScaleVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scVertexQtVisual::Move(targetMousePos, prevMousePos);

	scVector2D worldCoord = mCoordinateHelper->CameraToWorld(
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

	mParentFace->ScaleFace(dx, dy, dignalWorldCoord.x, dignalWorldCoord.y);
}

void scScaleVertexQtVisual::SetHorizontalScaleVector(const std::shared_ptr<scScaleVertexQtVisual>& scaleVector)
{
	mHorizontalScaleVertex = scaleVector;
}

void scScaleVertexQtVisual::SetVerticalScaleVector(const std::shared_ptr<scScaleVertexQtVisual>& scaleVector)
{
	mVerticalScaleVertex = scaleVector;
}

void scScaleVertexQtVisual::SetDiagonalScaleVector(const std::shared_ptr<scScaleVertexQtVisual>& scaleVector)
{
	mDiagonalScaleVertex = scaleVector;
}
