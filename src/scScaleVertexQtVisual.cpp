#include "scScaleVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"

using namespace std;

scScaleVertexQtVisual::scScaleVertexQtVisual(
	const std::shared_ptr<scFaceQtVisual>& face,
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

	auto targetLocalCoord = mCoordinateHelper->CameraToLocal(targetMousePos.x(), targetMousePos.y());
	auto prevLocalCoord = mCoordinateHelper->CameraToLocal(prevMousePos.x(), prevMousePos.y());

	double dx = targetLocalCoord.first / prevLocalCoord.first;
	double dy = targetLocalCoord.second / prevLocalCoord.second;
	mParentFace->ScaleFace(dx, dy);
}
