#pragma once
#include "scShapeInterface.h"

class scPolygon : public scShapeInterface
{
public:
	scPolygon(std::vector<QPoint>& points);
	virtual ~scPolygon();

	void Paint(QPainter& painter) override;

private:
	QString name;
	static int nameCnt;

};

