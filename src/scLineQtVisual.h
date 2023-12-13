#pragma once
#include "scLineData.h"
#include "scVertexQtVisual.h"

#include <QLineF>

class scLineQtVisual : public scShapeQtVisual
{
public:
	scLineQtVisual(
		const std::shared_ptr<scVertexQtVisual>& startVertex, 
		const std::shared_ptr<scVertexQtVisual>& endVertex,
		const QRect& viewportSize);
	~scLineQtVisual() override;

	void MoveShape(double dx, double dy) override;;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	std::shared_ptr<scLineData> GetLineData() const;

private:
	QLineF MakeQLineF();

	std::shared_ptr<scLineData> mLineData;
};

