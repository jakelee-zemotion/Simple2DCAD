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