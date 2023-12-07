#include "scLine.h"

using namespace std;

scLine::scLine(vector<QPoint>& points)
	:scShapeInterface(points)
{
}

scLine::~scLine()
{
}

void scLine::Paint(QPainter& painter)
{
	painter.drawPolyline(mPoints.data(), mPoints.size());
}
