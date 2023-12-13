#include "scLineData.h"

using namespace std;

scLineData::scLineData()
{
}

scLineData::~scLineData()
{

}

void scLineData::SetStartVertex(const shared_ptr<scVertexData>& startVertex)
{
	mStartVertex = startVertex;
}

void scLineData::SetEndVertex(const shared_ptr<scVertexData>& endVertex)
{
	mEndVertex = endVertex;
}

void scLineData::SetStartVertex(double x, double y)
{
	mStartVertex->SetX(x);
	mStartVertex->SetY(y);
}

void scLineData::SetEndVertex(double x, double y)
{
	mEndVertex->SetX(x);
	mEndVertex->SetY(y);
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
