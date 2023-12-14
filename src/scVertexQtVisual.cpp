#include "scVertexQtVisual.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(const QPointF& qpointF, const QRect& viewportSize)
	:scShapeQtVisual(viewportSize)
{
	// Set the position.
	mVertexData = make_shared<scVertexData>();

	pair<double, double> worldCoord = ScreenToWorld(qpointF.x(), qpointF.y());
	mVertexData->SetX(worldCoord.first);
	mVertexData->SetY(worldCoord.second);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::black;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::red;
	mShapeColors[static_cast<int>(COLOR_TYPE::CLICK)] = Qt::blue;
}

scVertexQtVisual::~scVertexQtVisual()
{
	qDebug() << "Vertex" << mShapeID.Get() << " Destruction";
}

QPointF scVertexQtVisual::MakeQPointF()
{
	pair<double, double> screenCoord 
		= WorldToScreen(mVertexData->GetX(), mVertexData->GetY());

	return { screenCoord.first, screenCoord.second };
}

void scVertexQtVisual::MoveShape(double dx, double dy)
{
	pair<double, double> screenCoord =
		WorldToScreen(mVertexData->GetX(), mVertexData->GetY());

	screenCoord.first += dx;
	screenCoord.second += dy;

	pair<double, double> worldCoord =
		ScreenToWorld(screenCoord.first, screenCoord.second);

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
		currMousePos.x() - 10.0, currMousePos.y() - 10.0,
		20.0, 20.0);

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
