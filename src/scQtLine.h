#pragma once
#include "scLineData.h"
#include "scQtVertex.h"

#include <QLineF>

class scQtLine : public scQtShapeInterface
{
public:
	scQtLine(std::shared_ptr<scQtVertex>& startVertex, std::shared_ptr<scQtVertex>& endVertex);
	~scQtLine();

	/*QPointF GetStartVertex();
	QPointF GetEndVertex();*/

	QLineF MakeQLineF();

	void Paint(QPainter& painter) override;

private:
	scLineData mLineData;
};

