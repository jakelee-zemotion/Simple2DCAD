#pragma once
#include <QPointF>
#include <QPainter>

class scCamera;
class scShapeQtVisual
{
public:
	scShapeQtVisual(const QRect& viewportSize);
	virtual ~scShapeQtVisual();

	virtual void MoveShape(double dx, double dy) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const QPointF& currMousePos) = 0;

protected:
	const QRect& mViewportSize;

	std::pair<double, double> WorldToScreen(double x, double y);
	std::pair<double, double> ScreenToWorld(double x, double y);
};

