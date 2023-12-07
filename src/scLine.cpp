#include "scLine.h"

using namespace std;

scLine::scLine(vector<QPoint>& points)
	:scShape(points)
{
	name = "Line" + QString::number(nameCnt++);
}

scLine::~scLine()
{
}

void scLine::Paint(QPainter& painter)
{
	painter.drawPolyline(mPoints.data(), mPoints.size());
}
