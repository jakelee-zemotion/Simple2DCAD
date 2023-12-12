#pragma once
#include <QPointF>
#include <QPainter>

class scCamera;
class scShapeQtVisual
{
public:
	scShapeQtVisual(const QRect& viewportSize);
	virtual ~scShapeQtVisual();

	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const QPointF& currMousePos) = 0;

protected:
	const QRect& mViewportSize;

	std::pair<double, double> WorldToScreen(double x, double y);
	std::pair<double, double> ScreenToWorld(double x, double y);

private:
	double WorldToScreenExpression(double value, double size);
	double ScreenToWorldExpression(double value, double size);
};

