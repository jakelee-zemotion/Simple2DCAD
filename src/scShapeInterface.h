#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class scShapeInterface
{
public:
	virtual void Paint(QPainter& painter) = 0;
	virtual ~scShapeInterface() = 0 {};

};

