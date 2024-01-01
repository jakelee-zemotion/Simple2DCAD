#include "scRotateControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <qDebug>

using namespace std;

scRotateControlVertexQtVisual::scRotateControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper)
{
	mShapeType = SHAPE_TYPE::ROTATE_CONTROL_VERTEX;

	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::darkGreen;
}

scRotateControlVertexQtVisual::~scRotateControlVertexQtVisual()
{
}

void scRotateControlVertexQtVisual::MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	scVector2D BB = mCoordinateHelper->CameraToLocal(prevMousePos);
	scVector2D CC = mCoordinateHelper->CameraToLocal(targetMousePos);

	shared_ptr<scCenterControlVertexQtVisual> centerVertex = dynamic_pointer_cast<scCenterControlVertexQtVisual>(mControlVertexVector.back());
	scVector2D AA = mCoordinateHelper->WorldToLocal(centerVertex->mVertexData->GetPos(), centerVertex->mVertexData->GetTransform());

	double a = VectorHelper::length(BB, CC);
	double b = VectorHelper::length(AA, BB);
	double c = VectorHelper::length(CC, AA);

	//qDebug() << b * c;

	if (b * c == 0.0)
		return;

	double crossZ = VectorHelper::crossZ(BB - AA, CC - AA);

	double sinX = crossZ / (b * c);

	angle += asin(sinX);

	mParentFace->RotateFace(targetMousePos, prevMousePos, angle);
}