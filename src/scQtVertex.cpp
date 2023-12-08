#include "scQtVertex.h"


scQtVertex::scQtVertex(QPoint& qpoint)
{
	mX = static_cast<double>(qpoint.x());
	mY = static_cast<double>(qpoint.y());

	this->setX(mX);
	this->setY(mY);
}

scQtVertex::scQtVertex(QPointF& qpointF)
{
	mX = qpointF.x();
	mY = qpointF.y();
}

scQtVertex::~scQtVertex()
{
}

double scQtVertex::GetX() const
{
	return mX;
}

double scQtVertex::GetY() const
{
	return mY;
}
