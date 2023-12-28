#pragma once
#include "scControlVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scScaleControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const BOX_POSITION& boxPos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void MoveControlVertexDirectly(const scVector2D& targetMousePos, const scVector2D& prevMousePos);

private:
	BOX_POSITION mBoxPos;

};

