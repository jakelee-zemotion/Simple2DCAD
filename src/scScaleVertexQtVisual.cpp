#include "scScaleVertexQtVisual.h"

#include "scFaceQtVisual.h"

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

	mParentFace->ScaleFace(0.9999, 0.9999);
}
