#include "Line.h"

Line::Line(QVector<QPoint> points)
	:Shape(points)
{
}

Line::~Line()
{
}

void Line::Paint(QPainter& painter)
{
	painter.drawPolyline(mPoints.data(), mPoints.size());
}
