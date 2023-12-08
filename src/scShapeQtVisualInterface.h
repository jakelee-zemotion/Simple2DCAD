#pragma once
#include <QPointF>
#include <QPainter>

class scShapeQtVisualInterface
{
public:
	virtual void Paint(QPainter& painter) = 0;
	virtual void HitTest(QPointF& currMousePos) = 0;

	virtual ~scShapeQtVisualInterface() = 0 {};
};

