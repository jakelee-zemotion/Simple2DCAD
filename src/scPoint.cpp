#include "scPoint.h"

#include <QPoint>

scPoint::scPoint(QPoint& qpoint)
{
	x = qpoint.x();
	y = qpoint.y();
}

scPoint::~scPoint()
{
}
