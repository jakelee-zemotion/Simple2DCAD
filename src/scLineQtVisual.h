#pragma once
#include "scShapeQtVisual.h"

#include <QLineF>

class scCoordinateHelper;
class scLineData;
class scVertexQtVisual;
class scLineQtVisual : public scShapeQtVisual
{
public:
	scLineQtVisual(
		SHAPE_TYPE shapeType,
		const std::shared_ptr<scVertexQtVisual>& startVertex, 
		const std::shared_ptr<scVertexQtVisual>& endVertex,
		const std::shared_ptr<scCoordinateHelper>& coordinate);
	~scLineQtVisual() override;

	void Move(double dx, double dy) override;;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	std::shared_ptr<scLineData> GetLineData() const;

private:
	QLineF MakeQLineF();

	std::shared_ptr<scLineData> mLineData;
};

