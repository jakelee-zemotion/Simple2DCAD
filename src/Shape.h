#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class Shape
{
public:
	Shape(std::vector<QPoint>& points);
	~Shape();

	virtual void Paint(QPainter& painter) = 0;

//protected:
	std::vector<QPoint> mPoints;
	QString name;

	static int nameCnt;
};

