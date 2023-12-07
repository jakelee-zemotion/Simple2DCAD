#include "scVertex.h"

#include <QPoint>

scVertex::scVertex(QPoint& qpoint)
{
	x = qpoint.x();
	y = qpoint.y();
}

scVertex::~scVertex()
{
}
