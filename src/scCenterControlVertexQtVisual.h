#pragma once
#include "scControlVertexQtVisual.h"

class scCenterControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scCenterControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const scCamera& camera, const QRect& viewportSize);

	~scCenterControlVertexQtVisual() override;

	void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) override;

private:

};

