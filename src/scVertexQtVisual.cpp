#include "scVertexQtVisual.h"

#include <QPainter>
#include <QDebug>

scVertexQtVisual::scVertexQtVisual(QPointF& qpointF)
{
	this->SetX(qpointF.x());
	this->SetY(qpointF.y());
}

scVertexQtVisual::~scVertexQtVisual()
{
}

QPointF scVertexQtVisual::MakeQPointF()
{
	return { vertexData.GetX(), vertexData.GetY() };
}

void scVertexQtVisual::SetX(double x)
{
	vertexData.SetX(x);
}

void scVertexQtVisual::SetY(double y)
{
	vertexData.SetY(y);
}

void scVertexQtVisual::SetVertex(QPointF& point)
{
	this->SetX(point.x());
	this->SetY(point.y());
}

double scVertexQtVisual::GetX() const
{
	return vertexData.GetX();
}

double scVertexQtVisual::GetY() const
{
	return vertexData.GetY();
}


void scVertexQtVisual::Paint(QPainter& painter)
{
	QPen pen(Qt::red);
	pen.setWidth(6);
	painter.setPen(pen);

	painter.drawPoint(this->MakeQPointF());
}

void scVertexQtVisual::HitTest(QPointF& currMousePos)
{
	QRectF rect(
		currMousePos.x() - 10.0, currMousePos.x() + 10.0, 
		currMousePos.y() - 10.0, currMousePos.y() + 10.0);

	if (rect.contains(this->MakeQPointF()))
	{
		//this->SetX(currMousePos.x());
		//this->SetY(currMousePos.y());

		qDebug() << "jih";
	}
}
