#include "scVertexData.h"

// qt
#include <qDebug>

scVertexData::scVertexData()
	:scShapeData()
{
	mPos = { 0.0, 0.0 };
}

void scVertexData::AddDelta(const scVector2D& delta)
{
	mPos += delta;
}

void scVertexData::SetPos(const scVector2D& position)
{
	mPos = position;
}

scVector2D scVertexData::GetPos() const
{
	return mPos;
}

scTransform& scVertexData::GetTransform()
{
	return mTransform;
}