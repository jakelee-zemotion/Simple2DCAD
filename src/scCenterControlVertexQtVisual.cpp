#include "scCenterControlVertexQtVisual.h"

using namespace std;

scCenterControlVertexQtVisual::scCenterControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper)
{
	mShapeType = SHAPE_TYPE::CENTER_CONTROL_VERTEX;
}

scCenterControlVertexQtVisual::~scCenterControlVertexQtVisual()
{
}

void scCenterControlVertexQtVisual::MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	scVertexQtVisual::Move(targetMousePos, prevMousePos);
}
