#include "scVertexData.h"

#include <qDebug>

scVertexData::scVertexData()
{
	mPos = { 0.0, 0.0 };
}

scVertexData::~scVertexData()
{
	//qDebug() << "VertexData Destruction";
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
