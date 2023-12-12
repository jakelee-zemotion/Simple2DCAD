#pragma once
#include <QPointF>
#include <QPainter>

class scCamera;
class scShapeQtVisual
{
public:
	scShapeQtVisual();
	virtual ~scShapeQtVisual();

	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(QPointF& currMousePos) = 0;

protected:
	//QRectF& mViewportSize;

	//QPointF WorldToScreen(QPointF point);
	//QPointF ScreenToWorld(QPointF point);
};

