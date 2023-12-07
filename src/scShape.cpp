#include "scShape.h"

using namespace std;

int scShape::nameCnt = 1;

scShape::scShape(vector<QPoint>& points)
	:mPoints(points)
{
}

scShape::~scShape()
{
}
