#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scScaleControlVertexQtVisual : public scVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& point,
		const BOX_POSITION& boxPos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void MoveControlVertexDirectly(const QPointF& targetMousePos, const QPointF& prevMousePos);

private:
	scFaceQtVisual* mParentFace;

	BOX_POSITION mBoxPos;

};

