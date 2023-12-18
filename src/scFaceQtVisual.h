#pragma once
#include "scFaceData.h"
#include "scLineQtVisual.h"

class scFaceQtVisual : public scShapeQtVisual
{
public:
	scFaceQtVisual(
		SHAPE_TYPE shapeType,
		const std::list<std::shared_ptr<scLineData>>& lineList, 
		const std::shared_ptr<scCoordinate>& coordinate);
	~scFaceQtVisual() override;

	void Move(double dx, double dy) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	void ScaleFace(double dx, double dy);
	void RotateFace(double theta);

private:
	QPolygonF MakeQPolygonF();

	std::shared_ptr<scFaceData> mFaceData;
};

