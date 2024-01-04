#include "scVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <QPointF>
#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(const scVector2D& pos, const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(scShapeType::VERTEX, coordinateHelper)
{
	// Set the position.
	mVertexData = make_shared<scVertexData>();

	this->SetXY(pos);

	// Set the colors.
	mShapeColors[static_cast<int>(scColorType::DEFAULT)] = Qt::darkCyan;
	mShapeColors[static_cast<int>(scColorType::HIGHTLIGHT)] = Qt::red;
	mShapeColors[static_cast<int>(scColorType::SELECT)] = Qt::blue;
}

scVertexQtVisual::~scVertexQtVisual()
{
}

void scVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos, mVertexData->GetTransform());

	scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
		prevMousePos, mVertexData->GetTransform());

	scVector2D delta = targetWorldCoord - prevWorldCoord;

	mVertexData->AddDelta(delta);
}

void scVertexQtVisual::Paint(QPainter& painter)
{
	Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(color);
	pen.setWidth(10);
	pen.setCapStyle(Qt::RoundCap);
	painter.setPen(pen);

	painter.drawPoint(this->MakeQPointF());
}

bool scVertexQtVisual::HitTest(const scVector2D& currMousePos)
{
	QPointF currQPointF = { currMousePos.x, currMousePos.y };

	QPointF vertex = this->MakeQPointF();

	QRectF rect(
		vertex.x() - mHitSize,
		vertex.y() - mHitSize,
		mHitSize * 2.0,
		mHitSize * 2.0);


	if (rect.contains(currQPointF))
	{
		return true;
	}

	return false;
}

scShapeID scVertexQtVisual::GetID() const
{
	return mVertexData->GetID();
}


void scVertexQtVisual::SetXY(const scVector2D& pos)
{
	// Unlike Line and Face, it moves directly to x, y.
	scVector2D worldCoord = mCoordinateHelper->CameraToWorld(
		pos, mVertexData->GetTransform());

	mVertexData->SetPos(worldCoord);
}

scVector2D scVertexQtVisual::GetXY() const
{
	scVector2D cameraCoord = mCoordinateHelper->WorldToCamera(
		mVertexData->GetPos(), mVertexData->GetTransform());

	return cameraCoord;
}


QPointF scVertexQtVisual::MakeQPointF() const
{
	scVector2D cameraCoord = this->GetXY();

	return { cameraCoord.x, cameraCoord.y };
}

