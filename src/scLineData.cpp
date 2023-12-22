#include "scLineData.h"

#include <qDebug>

using namespace std;

scLineData::scLineData()
{
}

scLineData::~scLineData()
{
	//qDebug() << "LineData Destruction";
}

void scLineData::AddDxDyToStart(double dx, double dy)
{
	mStartVertex->AddDx(dx);
	mStartVertex->AddDy(dy);
}

void scLineData::AddDxDyToEnd(double dx, double dy)
{
	mEndVertex->AddDx(dx);
	mEndVertex->AddDy(dy);
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

scTransform& scLineData::GetStartTransform()
{
	return mStartVertex->GetTransform();
}

scTransform& scLineData::GetEndTransform()
{
	return mEndVertex->GetTransform();
}
