#include "scPolyLine.h"

scPolyline::scPolyline(std::vector<QPoint> points)
	:scShapeInterface(points)
{
}

scPolyline::~scPolyline()
{
}

void scPolyline::Paint(QPainter& painter)
{
	painter.drawPolyline(mPoints.data(), mPoints.size());
}
