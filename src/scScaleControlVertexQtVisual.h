#pragma once
#include "scControlVertexQtVisual.h"

class scScaleControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const double& angleSum,
		const scBoxPosition& boxPos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) override;
	void Paint(QPainter& painter) override;

	const scBoxPosition mBoxPos;

private:
	const double& mAngleSum;
};

