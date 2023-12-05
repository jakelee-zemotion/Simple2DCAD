#pragma once
#include "Shape.h"

class Line :public Shape
{
public:
	Line(QVector<QPoint>& points);
	~Line();

	void Paint(QPainter& painter) override;
};

