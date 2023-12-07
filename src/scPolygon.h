#pragma once
#include "scShapeInterface.h"

class scPolygon : public scShapeInterface
{
public:
	scPolygon();
	virtual ~scPolygon() override;

	void Paint(QPainter& painter) override;

private:
	QString name;
	static int nameCnt;

};

