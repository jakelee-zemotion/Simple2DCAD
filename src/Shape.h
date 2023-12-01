#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class Shape
{
public:
	Shape();
	~Shape();

	virtual void Paint(QPainter& painter) = 0;

protected:
	QVector<QPoint> mPoints;
};

