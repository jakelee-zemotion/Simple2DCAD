#include "scLineData.h"

using namespace std;

scLineData::scLineData()
{
}

scLineData::~scLineData()
{

}

void scLineData::SetStartVertex(shared_ptr<scVertexVisualInterface> startVertex)
{
	mStartVertex = startVertex;
}

void scLineData::SetEndVertex(shared_ptr<scVertexVisualInterface> endVertex)
{
	mEndVertex = endVertex;
}

double scLineData::GetStartX() const
{
	return mStartVertex->GetX();
}

double scLineData::GetStartY() const
{
	return mStartVertex->GetY();
}

double scLineData::GetEndX() const
{
	return mEndVertex->GetX();
}

double scLineData::GetEndY() const
{
	return mEndVertex->GetY();
}
