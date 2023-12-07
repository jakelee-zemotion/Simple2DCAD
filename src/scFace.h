#pragma once
#include "scShape.h"

class scFace : public scShape
{
public:
	scFace(std::vector<QPoint>& points);
	virtual ~scFace();

	void Paint(QPainter& painter) override;
};

