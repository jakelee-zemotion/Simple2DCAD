#include "scQtLine.h"

using namespace std;

scQtLine::scQtLine(shared_ptr<scQtVertex>& startVertex, shared_ptr<scQtVertex>& endVertex)
{
	mLineData.SetStartVertex(startVertex);
	mLineData.SetEndVertex(endVertex);
}

scQtLine::~scQtLine()
{
}

QPointF scQtLine::GetStartVertex()
{
	return QPointF(mLineData.GetStartX(), mLineData.GetStartY());
}

QPointF scQtLine::GetEndVertex()
{
	return QPointF(mLineData.GetEndX(), mLineData.GetEndY());
}
