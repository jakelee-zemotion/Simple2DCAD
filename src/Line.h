#pragma once
#include "Shape.h"

class Line :public Shape
{
public:
	Line();
	~Line();

	void Paint(QPainter& painter) override;
};

