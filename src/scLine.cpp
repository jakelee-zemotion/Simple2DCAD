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

scVertex scLine::GetStartVertex() const
{
	//*mStartVertex.get() = scVertex(a);
	return *mStartVertex.get();
}

scVertex scLine::GetEndVertex() const
{
	return *mEndVertex.get();
}
