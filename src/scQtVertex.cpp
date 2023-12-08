#include "scQtVertex.h"

#include <QPainter>

scQtVertex::scQtVertex(QPoint& qpoint)
{
	double x = static_cast<double>(qpoint.x());
	double y = static_cast<double>(qpoint.y());

	this->SetX(x);
	this->SetY(y);
}

scQtVertex::scQtVertex(QPointF& qpointF)
{
	this->SetX(qpointF.x());
	this->SetY(qpointF.y());
}

scQtVertex::~scQtVertex()
{
}

QPointF scQtVertex::MakeQPointF()
{
	return { vertexData.GetX(), vertexData.GetY() };
}

void scQtVertex::SetX(double x)
{
	vertexData.SetX(x);
}

void scQtVertex::SetY(double y)
{
	vertexData.SetY(y);
}

double scQtVertex::GetX() const
{
	return vertexData.GetX();
}

double scQtVertex::GetY() const
{
	return vertexData.GetY();
}


void scQtVertex::Paint(QPainter& painter)
{
	QPen pen(Qt::red);
	pen.setWidth(6);
	painter.setPen(pen);

	painter.drawPoint(this->MakeQPointF());
}
