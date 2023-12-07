#pragma once
#include "scShape.h"

class scPolygon : public scShape
{
public:
	scPolygon(std::vector<QPoint>& points);
	virtual ~scPolygon();

	void Paint(QPainter& painter) override;
};

