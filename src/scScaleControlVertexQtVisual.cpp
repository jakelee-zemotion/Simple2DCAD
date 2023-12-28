#include "scScaleControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleControlVertexQtVisual::scScaleControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const BOX_POSITION& boxPos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper),
	     mBoxPos(boxPos)
{
	mShapeType = SHAPE_TYPE::CONTROL_VERTEX;
}

scScaleControlVertexQtVisual::~scScaleControlVertexQtVisual()
{
}

void scScaleControlVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	mParentFace->ScaleFace(targetMousePos, prevMousePos, mBoxPos);
}