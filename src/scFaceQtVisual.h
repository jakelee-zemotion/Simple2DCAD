#pragma once
#include "scFaceData.h"
#include "scLineQtVisual.h"

class scFaceQtVisual : public scShapeQtVisual
{
public:
	scFaceQtVisual(
		const std::list<std::shared_ptr<scLineData>>& lineList, 
		const QRect& viewportSize);
	~scFaceQtVisual() override;

	void MoveShape(double dx, double dy) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

private:
	std::vector<QPointF>& MakeQPolygonF();

	std::shared_ptr<scFaceData> mFaceData;
	std::vector<QPointF> mPolyVertices;
};

