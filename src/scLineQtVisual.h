#pragma once
#include "scLineData.h"
#include "scVertexQtVisual.h"

#include <QLineF>

class scLineQtVisual : public scShapeQtVisualInterface
{
public:
	scLineQtVisual(std::shared_ptr<scVertexQtVisual>& startVertex, std::shared_ptr<scVertexQtVisual>& endVertex);
	~scLineQtVisual();

	/*QPointF GetStartVertex();
	QPointF GetEndVertex();*/

	QLineF MakeQLineF();

	void Paint(QPainter& painter) override;
	void HitTest(QPointF& currMousePos) override;

private:
	scLineData mLineData;
};

