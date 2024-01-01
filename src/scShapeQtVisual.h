#pragma once
#include "scShapeID.h"
#include "scCommon.h"
#include "scMatrixVectorHelper.h"

#include <QPainter> // Due to Qt::GlobalColor

class scCamera;
class scCoordinateHelper;
class QPainter;
class scShapeQtVisual
{
public:
	scShapeQtVisual(const SHAPE_TYPE& shapeType);
	virtual ~scShapeQtVisual();

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const scVector2D& currMousePos) = 0;

	void SetShapeColorType(const COLOR_TYPE color);

	SHAPE_TYPE GetShapeType() const;

	scShapeID GetID() const;

protected:
	const double mHitSize = 10.0;
	const scShapeID mShapeID;

	SHAPE_TYPE mShapeType;
	COLOR_TYPE mShapeColorType;
	std::vector<Qt::GlobalColor> mShapeColors;

	std::unique_ptr<scCoordinateHelper> mCoordinateHelper;
};

