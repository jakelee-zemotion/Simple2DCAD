#pragma once

class QPoint;
#include <QPointF>
class scQtVertex : public QPointF
{
public:
	scQtVertex(QPoint& qpoint);
	scQtVertex(QPointF& qpointF);
	~scQtVertex();

	double GetX() const;
	double GetY() const;

private:
	double mX;
	double mY;
};

