#include "scVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(SHAPE_TYPE shapeType, const QPointF& qpointF, const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(shapeType, coordinateHelper)
{
	// Set the position.
	mVertexData = make_shared<scVertexData>();

	this->Move(qpointF.x(), qpointF.y());

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::black;
	mShapeColors[static_cast<int>(COLOR_TYPE::PUT_ON)] = Qt::red;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::cyan;
}

scVertexQtVisual::~scVertexQtVisual()
{
	qDebug() << "Vertex" << mShapeID.Get() << " Destruction";
}

QPointF scVertexQtVisual::MakeQPointF()
{
	pair<double, double> cameraCoord = 
		mCoordinateHelper->WorldToCamera(mVertexData->GetX(), mVertexData->GetY(), mVertexData->GetTransform());

	return { cameraCoord.first, cameraCoord.second };
}

void scVertexQtVisual::Move(double targetX, double targetY)
{
	// Unlike Line and Face, it moves directly to x, y.
	auto worldCoord = 
		mCoordinateHelper->CameraToWorld(targetX, targetY, mVertexData->GetTransform());

	mVertexData->SetX(worldCoord.first);
	mVertexData->SetY(worldCoord.second);
}

void scVertexQtVisual::Paint(QPainter& painter)
{
	Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(color);
	pen.setWidth(6);
	painter.setPen(pen);

	painter.drawPoint(this->MakeQPointF());
}

bool scVertexQtVisual::HitTest(const QPointF& currMousePos)
{
	QRectF rect(
		currMousePos.x() - mHitSize,
		currMousePos.y() - mHitSize,
		mHitSize * 2.0,
		mHitSize * 2.0);

	/*if (currMousePos.x() - 10.0 < this->GetX()
		&& currMousePos.x() + 10.0 > this->GetX()

		&& currMousePos.y() - 10.0 < this->GetY()
		&& currMousePos.y() + 10.0 > this->GetY())
	{
		return true;
	}*/

	if (rect.contains(this->MakeQPointF()))
	{
		return true;
	}

	return false;
}

shared_ptr<scVertexData> scVertexQtVisual::GetVertexData() const
{
	return mVertexData;
}
