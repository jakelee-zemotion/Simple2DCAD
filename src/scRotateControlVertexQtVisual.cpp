#include "scRotateControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <qDebug>

using namespace std;

scRotateControlVertexQtVisual::scRotateControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& point,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(point, coordinateHelper),
		 mParentFace(face)
{
	mShapeType = SHAPE_TYPE::ROTATE_VERTEX;

	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::darkGreen;
}

scRotateControlVertexQtVisual::~scRotateControlVertexQtVisual()
{
}

void scRotateControlVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	mParentFace->RotateFace(targetMousePos, prevMousePos);
}

void scRotateControlVertexQtVisual::MoveControlVertexDirectly(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x(), targetMousePos.y(), mVertexData->GetTransform());

	scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
		prevMousePos.x(), prevMousePos.y(), mVertexData->GetTransform());

	double dx = targetWorldCoord.x - prevWorldCoord.x;
	double dy = targetWorldCoord.y - prevWorldCoord.y;

	mVertexData->AddDx(dx);
	mVertexData->AddDy(dy);
}
