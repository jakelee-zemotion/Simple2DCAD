#pragma once
#include "Shape.h"

class Line :public Shape
{
public:
	Line(std::vector<QPoint>& points);
	~Line();

	void Paint(QPainter& painter) override;
};

