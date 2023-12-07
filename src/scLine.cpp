#include "scLine.h"
#include "scVertex.h"

using namespace std;

scLine::scLine(shared_ptr<scVertex>& startVertex, shared_ptr<scVertex>& endVertex)
	:mStartVertex(startVertex), mEndVertex(endVertex)
{
}

scLine::~scLine()
{
}

QPointF scLine::GetStartVertex() const
{
	return { (*mStartVertex.get()).GetX(), (*mStartVertex.get()).GetY() };
}

QPointF scLine::GetEndVertex() const
{
	return { (*mEndVertex.get()).GetX(), (*mEndVertex.get()).GetY() };
}
