#pragma once
#include "scShapeInterface.h"

class scPolyline : public scShapeInterface
{
public:
	scPolyline(std::vector<QPoint> points);
	~scPolyline();

	void Paint(QPainter& painter) override;
private:

};

