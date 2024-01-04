#include "scScaleControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleControlVertexQtVisual::scScaleControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const scBoxPosition& boxPos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper),
	     mBoxPos(boxPos)
{
	mShapeType = scShapeType::SCALE_CONTROL_VERTEX;
}

scScaleControlVertexQtVisual::~scScaleControlVertexQtVisual()
{
}

void scScaleControlVertexQtVisual::MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	mParentFace->ScaleFace(targetMousePos, prevMousePos, mBoxPos, angle);
}