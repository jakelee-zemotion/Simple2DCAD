#include "scCenterControlVertexQtVisual.h"

using namespace std;

scCenterControlVertexQtVisual::scCenterControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scControlVertexQtVisual(face, pos, coordinateHelper)
{
}

scCenterControlVertexQtVisual::~scCenterControlVertexQtVisual()
{
}

void scCenterControlVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
}
