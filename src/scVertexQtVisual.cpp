#include "scVertexQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(const QPointF& point, const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(SHAPE_TYPE::VERTEX, coordinateHelper)
{
	Initialize(point);
}


scVertexQtVisual::scVertexQtVisual(
	const SHAPE_TYPE shapeType, 
	const QPointF& point, 
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scShapeQtVisual(shapeType, coordinateHelper)
{
	Initialize(point);
}

void scVertexQtVisual::Initialize(const QPointF& point)
{
	// Set the position.
	mVertexData = make_shared<scVertexData>();

	this->Move(point);

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
	pair<double, double> cameraCoord = 
		mCoordinateHelper->WorldToCamera(mVertexData->GetX(), mVertexData->GetY(), mVertexData->GetTransform());

	return { cameraCoord.first, cameraCoord.second };
}


void scVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	// Unlike Line and Face, it moves directly to x, y.
	auto worldCoord = 
		mCoordinateHelper->CameraToWorld(targetMousePos.x(), targetMousePos.y(), mVertexData->GetTransform());

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

	if (rect.contains(currMousePos))
	{
		return true;
	}

	return false;
}

shared_ptr<scVertexData> scVertexQtVisual::GetVertexData() const
{
	return mVertexData;
}
