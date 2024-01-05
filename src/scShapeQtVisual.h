#pragma once

// qt
#include <QPainter> // Due to Qt::GlobalColor

// Simple2DCAD
#include "scShapeID.h"
#include "scCommon.h"
#include "scMatrixVectorHelper.h"

// Forward Declaration
class scCamera;
class scCoordinateHelper;

class scShapeQtVisual
{
// [Member function section]
public:
	scShapeQtVisual(const scShapeType& shapeType, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scShapeQtVisual();

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) = 0;
	virtual void Paint(QPainter& painter) = 0;
	virtual bool HitTest(const scVector2D& currMousePos) = 0;
	virtual scShapeID GetID() const = 0;

	void SetShapeColorType(const scColorType& color);

	scShapeType GetShapeType() const;

// [Member variable section]
protected:
	const double mHitSize;
	const std::shared_ptr<scCoordinateHelper>& mCoordinateHelper;

	scShapeType mShapeType;
	scColorType mShapeColorType;
	std::vector<Qt::GlobalColor> mShapeColors;
};

