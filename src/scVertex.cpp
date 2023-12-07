#include "scVertex.h"

#include <QPointF>

scVertex::scVertex(QPoint& qpoint)
{
	mX = static_cast<double>(qpoint.x());
	mY = static_cast<double>(qpoint.y());
}

scVertex::scVertex(QPointF& qpointF)
{
	mX = qpointF.x();
	mY = qpointF.y();
}

scVertex::~scVertex()
{
}
