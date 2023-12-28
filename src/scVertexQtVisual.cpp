#include "scVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <QPointF>
#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(const scVector2D& pos, const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(SHAPE_TYPE::VERTEX, coordinateHelper)
{
	// Set the position.
	mVertexData = make_shared<scVertexData>();

	this->Move(pos);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::black;
	mShapeColors[static_cast<int>(COLOR_TYPE::HIGHTLIGHT)] = Qt::red;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::blue;
}

scVertexQtVisual::~scVertexQtVisual()
{
	qDebug() << "Vertex" << mShapeID.Get() << " Destruction";
}

QPointF scVertexQtVisual::MakeQPointF()
{
	scVector2D cameraCoord = mCoordinateHelper->WorldToCamera(
		mVertexData->GetX(), mVertexData->GetY(), mVertexData->GetTransform());

	return { cameraCoord.x, cameraCoord.y };
}


void scVertexQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	// Unlike Line and Face, it moves directly to x, y.
	scVector2D worldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x, targetMousePos.y, mVertexData->GetTransform());

	mVertexData->SetX(worldCoord.x);
	mVertexData->SetY(worldCoord.y);
}

void scVertexQtVisual::Paint(QPainter& painter)
{
	Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(color);
	pen.setWidth(6);
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

	/*if (currMousePos.x() - 10.0 < this->GetX()
		&& currMousePos.x() + 10.0 > this->GetX()

		&& currMousePos.y() - 10.0 < this->GetY()
		&& currMousePos.y() + 10.0 > this->GetY())
	{
		return true;
	}*/

	if (rect.contains(currQPointF))
	{
		return true;
	}

	return false;
}