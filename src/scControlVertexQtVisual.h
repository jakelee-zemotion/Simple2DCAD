#pragma once

// Simple2DCAD
#include "scVertexQtVisual.h"

// Forward Declaration
class scCoordinateHelper;
class scFaceQtVisual;

class scControlVertexQtVisual : public scVertexQtVisual
{
// [Member function section]
public:
	scControlVertexQtVisual(scFaceQtVisual* face, const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scControlVertexQtVisual();

	virtual void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) = 0;
	void MultiplyRotateXY(double angle, double transX, double transY);
	void MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY, double angle);

	scVector2D GetLocalXY() const;

// [Member variable section]
protected:
	scFaceQtVisual* mParentFace;
};

