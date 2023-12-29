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
	mStartVertex->Add({ dx, dy });
}

void scLineData::AddDxDyToEnd(double dx, double dy)
{
	mEndVertex->Add({ dx, dy });
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
	mStartVertex->SetXY({ x, y });
}

void scLineData::SetEndVertex(double x, double y)
{
	mEndVertex->SetXY({ x, y });
}

double scLineData::GetStartX() const
{
	return mStartVertex->GetXY().x;
}

double scLineData::GetStartY() const
{
	return mStartVertex->GetXY().y;
}

double scLineData::GetEndX() const
{
	return mEndVertex->GetXY().x;
}

double scLineData::GetEndY() const
{
	return mEndVertex->GetXY().y;
}

scTransform& scLineData::GetStartTransform()
{
	return mStartVertex->GetTransform();
}

scTransform& scLineData::GetEndTransform()
{
	return mEndVertex->GetTransform();
}
