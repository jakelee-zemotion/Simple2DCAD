#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class scShapeInterface
{
public:
	scShapeInterface(std::vector<QPoint>& points) : mPoints(points) {};
	virtual ~scShapeInterface() = 0 {};

	virtual void Paint(QPainter& painter) = 0;

//protected:
	std::vector<QPoint> mPoints;

};

