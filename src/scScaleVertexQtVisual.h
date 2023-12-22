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

	void SetHorizontalScaleVector(const std::shared_ptr<scScaleVertexQtVisual>& scaleVector);
	void SetVerticalScaleVector(const std::shared_ptr<scScaleVertexQtVisual>& scaleVector);

private:
	const std::shared_ptr<scFaceQtVisual> mParentFace;

	std::weak_ptr<scScaleVertexQtVisual> mHorizontalScaleVertex;
	std::weak_ptr<scScaleVertexQtVisual> mVerticalScaleVertex;
};

