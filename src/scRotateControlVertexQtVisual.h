#pragma once
#include "scControlVertexQtVisual.h"

class scRotateControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scRotateControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scRotateControlVertexQtVisual();

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;

private:
};

