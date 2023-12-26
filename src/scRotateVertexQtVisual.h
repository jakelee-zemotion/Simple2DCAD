#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scRotateVertexQtVisual : public scVertexQtVisual
{
public:
	scRotateVertexQtVisual(
		const std::shared_ptr<scFaceQtVisual>& face,
		const QPointF& point,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scRotateVertexQtVisual();

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;

private:
	const std::shared_ptr<scFaceQtVisual> mParentFace;
};

