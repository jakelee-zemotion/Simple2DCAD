#include "scVertexQtVisual.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scVertexQtVisual::scVertexQtVisual(QPointF& qpointF)
{
	mVertexData = make_shared<scVertexData>();
	this->SetX(qpointF.x());
	this->SetY(qpointF.y());

	mPenColor = Qt::red;
}

scVertexQtVisual::~scVertexQtVisual()
{
}

QPointF scVertexQtVisual::MakeQPointF()
{
	return { mVertexData->GetX(), mVertexData->GetY() };
}

void scVertexQtVisual::SetX(double x)
{
	mVertexData->SetX(x);
}

void scVertexQtVisual::SetY(double y)
{
	mVertexData->SetY(y);
}

double scVertexQtVisual::GetX() const
{
	return mVertexData->GetX();
}

double scVertexQtVisual::GetY() const
{
	return mVertexData->GetY();
}


void scVertexQtVisual::Paint(QPainter& painter)
{
	QPen pen(mPenColor);
	pen.setWidth(6);
	painter.setPen(pen);

	painter.drawPoint(this->MakeQPointF());
}

bool scVertexQtVisual::HitTest(QPointF& currMousePos)
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