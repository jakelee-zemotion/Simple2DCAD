#pragma once
#include "scShapeInterface.h"

class scLine;
class scPolyline : public scShapeInterface
{
public:
	scPolyline(std::vector<QPoint> points);
	~scPolyline();

	void Paint(QPainter& painter) override;

private:
	std::list<std::shared_ptr<scLine>> mLineList;

};

