#pragma once
#include "scLineData.h"
#include "scVertexQtVisual.h"

#include <QLineF>

class scLineQtVisual : public scShapeQtVisual
{
public:
	scLineQtVisual(
		std::shared_ptr<scVertexQtVisual>& startVertex, 
		std::shared_ptr<scVertexQtVisual>& endVertex,
		const QRect& viewportSize);
	~scLineQtVisual() override;

	QLineF MakeQLineF();

	void MoveShape(double dx, double dy) override;;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

private:
	std::shared_ptr<scLineData> mLineData;
};

