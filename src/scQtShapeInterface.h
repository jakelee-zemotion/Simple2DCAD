#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class scQtShapeInterface
{
public:
	virtual void Paint(QPainter& painter) = 0;
	virtual ~scQtShapeInterface() = 0 {};
};

