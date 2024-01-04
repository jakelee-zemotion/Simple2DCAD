#pragma once

// Simple2DCAD
#include "scControlVertexQtVisual.h"

class scCenterControlVertexQtVisual : public scControlVertexQtVisual
{
// [Member function section]
public:
	scCenterControlVertexQtVisual(scFaceQtVisual* face, const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scCenterControlVertexQtVisual() override;

	void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) override;
	void Paint(QPainter& painter) override;

private:

};

