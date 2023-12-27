#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scRotateControlVertexQtVisual : public scVertexQtVisual
{
public:
	scRotateControlVertexQtVisual(
		scFaceQtVisual* face,
		const QPointF& point,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scRotateControlVertexQtVisual();

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;

private:
	scFaceQtVisual* mParentFace;
};

