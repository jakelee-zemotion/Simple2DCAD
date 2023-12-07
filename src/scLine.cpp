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