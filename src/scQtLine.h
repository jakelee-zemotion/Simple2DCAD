#pragma once
#include "scLineData.h"
#include "scQtVertex.h"

#include <QLineF>

class scQtLine : QLineF
{
public:
	scQtLine(std::shared_ptr<scQtVertex>& startVertex, std::shared_ptr<scQtVertex>& endVertex);
	~scQtLine();

	QPointF GetStartVertex();
	QPointF GetEndVertex();

private:
	scLineData mLineData;
};

