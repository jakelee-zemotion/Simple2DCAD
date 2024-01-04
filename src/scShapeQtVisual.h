#pragma once

// qt
#include <QPainter> // Due to Qt::GlobalColor

// Simple2DCAD
#include "scShapeID.h"
#include "scCommon.h"
#include "scMatrixVectorHelper.h"

class scCamera;
class scCoordinateHelper;
class scShapeQtVisual
{
public:
	scShapeQtVisual(const scShapeType& shapeType, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scShapeQtVisual();

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const scVector2D& currMousePos) = 0;
	virtual scShapeID GetID() const = 0;

	void SetShapeColorType(const scColorType color);

	scShapeType GetShapeType() const;


protected:
	const double mHitSize = 10.0;

	scShapeType mShapeType;
	scColorType mShapeColorType;
	std::vector<Qt::GlobalColor> mShapeColors;

	const std::shared_ptr<scCoordinateHelper>& mCoordinateHelper;
};

