#pragma once

// Simple2DCAD
#include "scControlVertexQtVisual.h"

class scScaleControlVertexQtVisual : public scControlVertexQtVisual
{
// [Member function section]
public:
	scScaleControlVertexQtVisual(const std::shared_ptr<scFaceQtVisual> face, const scVector2D& pos, const double& angleSum, const scBoxPosition& boxPos, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scScaleControlVertexQtVisual() override;

	void ScaleFace(const scVector2D& scale, const scVector2D& trans, const double angle);
	void Paint(QPainter& painter) override;

	scBoxPosition GetBoxPosition() const;

// [Member variable section]
private:
	const double& mAngleSum;
	const scBoxPosition mBoxPos;
};

