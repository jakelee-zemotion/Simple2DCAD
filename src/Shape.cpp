#include "Shape.h"

int Shape::nameCnt = 1;

Shape::Shape(QVector<QPoint> points)
	:mPoints(points)
{
}

Shape::~Shape()
{
}
