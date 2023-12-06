#include "Face.h"
#include <qDebug>

using namespace std;

Face::Face(vector<QPoint>& points)
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


	QPolygon qqqq({ {100, 100}, {100, 200}, {400, 400}, {200, 100} });

	qDebug() << qqqq.containsPoint({ 89, 90 }, Qt::OddEvenFill);

	painter.drawPolygon(qqqq);
}
