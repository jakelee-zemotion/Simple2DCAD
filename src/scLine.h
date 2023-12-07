#pragma once
#include "scShapeInterface.h"

class scLine : public scShapeInterface
{
public:
	scLine(std::vector<QPoint>& points);
	~scLine();

	void Paint(QPainter& painter) override;
};

