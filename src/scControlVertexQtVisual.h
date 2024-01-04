#pragma once

// Simple2DCAD
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scControlVertexQtVisual : public scVertexQtVisual
{
public:
	scControlVertexQtVisual(scFaceQtVisual* face, const scVector2D& pos, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scControlVertexQtVisual();

	virtual void MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle) = 0;

protected:
	scFaceQtVisual* mParentFace;

};

