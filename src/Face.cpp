#include "Face.h"

Face::Face(QVector<QPoint>& points)
	:Shape(points)
{
	name = "Face" + QString::number(nameCnt++);
}

Face::~Face()
{
}

void Face::Paint(QPainter& painter)
{
	painter.drawPolygon(mPoints.data(), mPoints.size());
}
