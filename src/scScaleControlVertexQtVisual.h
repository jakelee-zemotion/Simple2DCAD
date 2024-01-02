#pragma once
#include "scControlVertexQtVisual.h"

class scScaleControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const BOX_POSITION& boxPos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) override;
	BOX_POSITION mBoxPos;

private:

};

