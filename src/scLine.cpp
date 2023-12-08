#include "scLine.h"
#include "scQtVertex.h"

using namespace std;

scLine::scLine(shared_ptr<scQtVertex>& startVertex, shared_ptr<scQtVertex>& endVertex)
	:mStartVertex(startVertex), mEndVertex(endVertex)
{
}

scLine::~scLine()
{
}

scQtVertex scLine::GetStartVertex() const
{
	return *mStartVertex.get();
}

scQtVertex scLine::GetEndVertex() const
{
	return *mEndVertex.get();
}
