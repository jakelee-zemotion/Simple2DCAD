#pragma once
#include "scShapeID.h"
#include "scheader.h"

#include <QPointF>
#include <QPainter>

class scCamera;
class scShapeQtVisual
{
public:
	scShapeQtVisual(SHAPE_TYPE shapeType, const QRect& viewportSize);
	virtual ~scShapeQtVisual();

	virtual void MoveShape(double dx, double dy) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const QPointF& currMousePos) = 0;

	void SetShapeColorType(const COLOR_TYPE color);

	SHAPE_TYPE GetShapeType() const;

	scShapeID GetID() const;

protected:
	const double mHitSize;
	const SHAPE_TYPE mShapeType;

	const QRect& mViewportSize;
	scShapeID mShapeID;
	COLOR_TYPE mShapeColorType;
	std::vector<Qt::GlobalColor> mShapeColors;

	std::pair<double, double> WorldToScreen(double x, double y);
	std::pair<double, double> ScreenToWorld(double x, double y);

	std::pair<double, double> ScreenToTransfrom(double x, double y);
};

