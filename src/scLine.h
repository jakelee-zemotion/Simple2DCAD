#pragma once
#include "scShape.h"

class scLine :public scShape
{
public:
	scLine(std::vector<QPoint>& points);
	~scLine();

	void Paint(QPainter& painter) override;
};

