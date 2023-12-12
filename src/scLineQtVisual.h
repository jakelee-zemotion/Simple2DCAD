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

	void MoveLine(double dx, double dy);

	QLineF MakeQLineF();

	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

private:
	std::shared_ptr<scLineData> mLineData;
};

