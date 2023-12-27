#pragma once
#include "scVertexQtVisual.h"

class scCoordinateHelper;
class scFaceQtVisual;
class scScaleControlVertexQtVisual : public scVertexQtVisual
{
public:
	scScaleControlVertexQtVisual(
		scFaceQtVisual* face,
		const QPointF& point, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	~scScaleControlVertexQtVisual() override;

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;
	void MoveControlVertexDirectly(const QPointF& targetMousePos, const QPointF& prevMousePos);

	void SetHorizontalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector);
	void SetVerticalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector);
	void SetDiagonalScaleVector(const std::shared_ptr<scScaleControlVertexQtVisual>& scaleVector);

private:
	scFaceQtVisual* mParentFace;

	std::weak_ptr<scScaleControlVertexQtVisual> mHorizontalScaleVertex;
	std::weak_ptr<scScaleControlVertexQtVisual> mVerticalScaleVertex;
	std::weak_ptr<scScaleControlVertexQtVisual> mDiagonalScaleVertex;

};

