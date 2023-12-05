#include "Line.h"

using namespace std;

Line::Line(vector<QPoint>& points)
	:Shape(points)
{
	name = "Line" + QString::number(nameCnt++);
}

Line::~Line()
{
}

void Line::Paint(QPainter& painter)
{
	painter.drawPolyline(mPoints.data(), mPoints.size());
}
