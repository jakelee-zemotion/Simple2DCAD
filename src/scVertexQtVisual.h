#pragma once

// Simple2DCAD
#include "scShapeQtVisual.h"

// Forward Declaration
class scCoordinateHelper;
class scVertexData;

class scVertexQtVisual : public scShapeQtVisual
{
// [Member function section]
public:
	scVertexQtVisual(const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scVertexQtVisual() override;

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;
	scShapeID GetID() const override;

	void SetXY(const scVector2D& pos);
	scVector2D GetXY() const;

	friend class scLineQtVisual;

protected:
	QPointF MakeQPointF() const;

	std::shared_ptr<scVertexData> mVertexData;
};

