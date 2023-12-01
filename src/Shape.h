#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class Shape
{
public:
	Shape(QVector<QPoint>& points);
	~Shape();

	virtual void Paint(QPainter& painter) = 0;

protected:
	QVector<QPoint> mPoints;
};

