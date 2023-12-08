#include "scQtVertex.h"


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

void scQtVertex::SetX(double x)
{
	vertexData.SetX(x);
	this->setX(x);
}

void scQtVertex::SetY(double y)
{
	vertexData.SetY(y);
	this->setY(y);
}

double scQtVertex::GetX() const
{
	return vertexData.GetX();
}

double scQtVertex::GetY() const
{
	return vertexData.GetY();
}
