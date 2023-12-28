#pragma once
#include "scControlVertexQtVisual.h"

class scCenterControlVertexQtVisual : public scControlVertexQtVisual
{
public:
	scCenterControlVertexQtVisual(
		scFaceQtVisual* face,
		const scVector2D& pos,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scCenterControlVertexQtVisual();

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;

private:

};

