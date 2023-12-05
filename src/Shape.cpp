#include "Shape.h"

using namespace std;

int Shape::nameCnt = 1;

Shape::Shape(vector<QPoint>& points)
	:mPoints(points)
{
}

Shape::~Shape()
{
}
