#pragma once
#include "Shape.h"

class Face : public Shape
{
public:
	Face(QVector<QPoint>& points);
	virtual ~Face();

	void Paint(QPainter& painter) override;
};

