#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scRotateControlVertexQtVisual : public scVertexQtVisual
{
public:
	scRotateControlVertexQtVisual(
		const std::shared_ptr<scFaceQtVisual>& face,
		const QPointF& point,
		const QPointF& center,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scRotateControlVertexQtVisual();

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;

private:
	const std::shared_ptr<scFaceQtVisual> mParentFace;
	const QPointF mCenter;
};

