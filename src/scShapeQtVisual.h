#pragma once
#include "scShapeID.h"
#include "scCommon.h"

#include <QPointF>
#include <QPainter>

class scCamera;
class scCoordinateHelper;
class scShapeQtVisual
{
public:
	scShapeQtVisual(SHAPE_TYPE shapeType, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scShapeQtVisual();

	virtual void Move(double dx, double dy) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const QPointF& currMousePos) = 0;

	void SetShapeColorType(const COLOR_TYPE color);

	SHAPE_TYPE GetShapeType() const;

	scShapeID GetID() const;

protected:
	const double mHitSize;
	const SHAPE_TYPE mShapeType;

	scShapeID mShapeID;
	COLOR_TYPE mShapeColorType;
	std::vector<Qt::GlobalColor> mShapeColors;

	const std::shared_ptr<scCoordinateHelper>& mCoordinateHelper;
};

