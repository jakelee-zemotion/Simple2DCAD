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

void scLineData::SetStartVertexScale(double scaleX, double scaleY)
{
	mStartVertex->SetScaleX(scaleX);
	mStartVertex->SetScaleY(scaleY);
}

void scLineData::SetEndVertexScale(double scaleX, double scaleY)
{
	mEndVertex->SetScaleX(scaleX);
	mEndVertex->SetScaleY(scaleY);
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


double scLineData::GetStartScaleX() const
{
	return mStartVertex->GetScaleX();
}

double scLineData::GetStartScaleY() const
{
	return mStartVertex->GetScaleY();
}

double scLineData::GetEndScaleX() const
{
	return mEndVertex->GetScaleX();
}

double scLineData::GetEndScaleY() const
{
	return mEndVertex->GetScaleY();
}
