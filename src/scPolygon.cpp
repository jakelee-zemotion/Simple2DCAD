#include "scPolygon.h"
#include <qDebug>
#include <QLineF>

using namespace std;

scPolygon::scPolygon(vector<QPoint>& points)
	:scShape(points)
{
	name = "Face" + QString::number(nameCnt++);
}

scPolygon::~scPolygon()
{
}

void scPolygon::Paint(QPainter& painter)
{
	painter.drawPolygon(mPoints.data(), mPoints.size());

	//QPolygon qqqq({ {100, 100}, {100, 200}, {400, 400}, {200, 100} });
	////qDebug() << qqqq.containsPoint({ 89, 90 }, Qt::OddEvenFill);

	//QPoint p(150, 150);
	//QLineF li({ 100, 100 }, { 200, 200 });

	//QPointF intersectPnt;
	//QLineF line(p.x() - 10, p.y() - 10, p.x() + 10, p.y() + 10);
	//qDebug() << (li.intersects(line, &intersectPnt) == QLineF::BoundedIntersection );

	//painter.drawPolygon(qqqq);
	//painter.drawLine(li);
}
