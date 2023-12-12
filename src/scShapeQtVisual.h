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

	QPointF WorldToScreen(QPointF point);
	QPointF ScreenToWorld(QPointF point);
};

