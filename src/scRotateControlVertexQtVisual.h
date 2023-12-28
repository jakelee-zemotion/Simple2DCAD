#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scRotateControlVertexQtVisual : public scVertexQtVisual
{
public:
	scRotateControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& point,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scRotateControlVertexQtVisual();

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void MoveControlVertexDirectly(const scVector2D& targetMousePos, const scVector2D& prevMousePos);

private:
	scFaceQtVisual* mParentFace;
};

