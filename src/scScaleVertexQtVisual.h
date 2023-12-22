#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scScaleVertexQtVisual : public scVertexQtVisual
{
public:
	scScaleVertexQtVisual(
		const std::shared_ptr<scFaceQtVisual>& face, 
		const QPointF& point, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleVertexQtVisual() override;

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;

private:
	const std::shared_ptr<scFaceQtVisual> mParentFace;
};

