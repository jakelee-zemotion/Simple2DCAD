#pragma once
#include "scShapeQtVisual.h"

class scCoordinateHelper;
class scVertexData;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scVertexQtVisual() override;

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos = scVector2D(0.0, 0.0)) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;

	QPointF MakeQPointF();

	friend class scLineQtVisual;

	std::shared_ptr<scVertexData> mVertexData;

protected:
};

