#pragma once
#include "Shape.h"

class Face : public Shape
{
public:
	Face(QVector<QPoint> points);
	~Face();

	void Paint(QPainter& painter) override;
};

