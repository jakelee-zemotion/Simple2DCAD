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

	void MultiplyRotateXY(const scVector2D& trans, const double angle);
	void MultiplyScaleXY(const scVector2D& scale, const scVector2D& trans, const double angle);

	scVector2D GetLocalXY() const;

// [Member variable section]
protected:
	scFaceQtVisual* mParentFace;
};

