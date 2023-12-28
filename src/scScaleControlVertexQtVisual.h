#pragma once
#include "scVertexQtVisual.h"
#include "scCommon.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scScaleControlVertexQtVisual : public scVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const QPointF& point, 
		const BOX_POSITION& boxPos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;
	void MoveControlVertexDirectly(const QPointF& targetMousePos, const QPointF& prevMousePos);

private:
	scFaceQtVisual* mParentFace;

	BOX_POSITION mBoxPos;

};

