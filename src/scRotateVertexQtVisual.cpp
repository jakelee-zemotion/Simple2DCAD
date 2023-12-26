#include "scRotateVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"

using namespace std;

scRotateVertexQtVisual::scRotateVertexQtVisual(
	const shared_ptr<scFaceQtVisual>& face, 
	const QPointF& point, 
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scVertexQtVisual(SHAPE_TYPE::ROTATE_VERTEX, point, coordinateHelper),
	mParentFace(face)
{
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::darkGreen;
}

scRotateVertexQtVisual::~scRotateVertexQtVisual()
{
}

void scRotateVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scVertexQtVisual::Move(targetMousePos, prevMousePos);

	
}
