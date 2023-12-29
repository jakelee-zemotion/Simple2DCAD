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

void scVertexData::Add(const scVector2D& pos)
{
	mPos += pos;
}

void scVertexData::SetXY(const scVector2D& pos)
{
	mPos = pos;
}

scVector2D scVertexData::GetXY() const
{
	return mPos;
}

scTransform& scVertexData::GetTransform()
{
	return mTransform;
}
