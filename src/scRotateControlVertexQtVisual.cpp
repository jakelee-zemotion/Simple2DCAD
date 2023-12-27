#include "scRotateControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"

#include <qDebug>

using namespace std;

scRotateControlVertexQtVisual::scRotateControlVertexQtVisual(
	const shared_ptr<scFaceQtVisual>& face, 
	const QPointF& point,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(SHAPE_TYPE::ROTATE_VERTEX, point, coordinateHelper),
		 mParentFace(face)
{
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::darkGreen;
}

scRotateControlVertexQtVisual::~scRotateControlVertexQtVisual()
{
}

void scRotateControlVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	//scVertexQtVisual::Move(targetMousePos, prevMousePos);


	mParentFace->RotateFace(targetMousePos, prevMousePos);
}
