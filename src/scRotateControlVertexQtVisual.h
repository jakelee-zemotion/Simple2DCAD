#pragma once

// Simple2DCAD
#include "scControlVertexQtVisual.h"

class scRotateControlVertexQtVisual : public scControlVertexQtVisual
{
// [Member function section]
public:
	scRotateControlVertexQtVisual(const std::shared_ptr<scFaceQtVisual> face, const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scRotateControlVertexQtVisual() override;

	void RotateFace(const scVector2D& trans, const double angle);
	void Paint(QPainter& painter) override;

private:
};

