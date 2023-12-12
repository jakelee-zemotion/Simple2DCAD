#include "scVertexQtVisual.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(const QPointF& qpointF, const QRect& viewportSize)
	:scShapeQtVisual(viewportSize)
{
	mVertexData = make_shared<scVertexData>();
	this->SetXY(qpointF.x(), qpointF.y());

	mPenColor = Qt::red;
	qDebug() << mViewportSize.width();
}

scVertexQtVisual::~scVertexQtVisual()
{
}

QPointF scVertexQtVisual::MakeQPointF()
{
	return { mVertexData->GetX(), mVertexData->GetY() };
}

void scVertexQtVisual::SetXY(double x, double y)
{
	mVertexData->SetX(x);
	mVertexData->SetY(y);
}

void scVertexQtVisual::Paint(QPainter& painter)
{
	QPen pen(mPenColor);
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
