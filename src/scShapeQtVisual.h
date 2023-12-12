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

	double WorldToScreenX(double x);
	double WorldToScreenY(double y);

	double ScreenToWorldX(double x);
	double ScreenToWorldY(double y);

private:
	double WorldToScreen(double value, double size);
	double ScreenToWorld(double value, double size);
};

