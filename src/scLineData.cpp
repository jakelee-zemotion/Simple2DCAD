#include "scLineData.h"

// qt
#include <qDebug>

using namespace std;

scLineData::scLineData()
	:scShapeData()
{
}

void scLineData::AddDeltaToStart(const scVector2D& delta)
{
	mStartVertex->AddDelta(delta);
}

void scLineData::AddDeltaToEnd(const scVector2D& delta)
{
	mEndVertex->AddDelta(delta);
}

void scLineData::SetStartVertex(const shared_ptr<scVertexData>& startVertex)
{
	mStartVertex = startVertex;
}

void scLineData::SetEndVertex(const shared_ptr<scVertexData>& endVertex)
{
	mEndVertex = endVertex;
}

void scLineData::SetPosToStartVertex(const scVector2D& position)
{
	mStartVertex->SetPos(position);
}

void scLineData::SetPosToEndVertex(const scVector2D& position)
{
	mEndVertex->SetPos(position);
}

scVector2D scLineData::GetStartPos() const
{
	return mStartVertex->GetPos();
}

scVector2D scLineData::GetEndPos() const
{
	return mEndVertex->GetPos();
}

scTransform& scLineData::GetStartTransform()
{
	return mStartVertex->GetTransform();
}

scTransform& scLineData::GetEndTransform()
{
	return mEndVertex->GetTransform();
}

scShapeID scLineData::GetStartID() const
{
	return mStartVertex->GetID();
}

scShapeID scLineData::GetEndID() const
{
	return mEndVertex->GetID();
}
