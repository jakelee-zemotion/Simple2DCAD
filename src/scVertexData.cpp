#include "scVertexData.h"

scVertexData::scVertexData()
{
	mX = 0.0;
	mY = 0.0;
}

scVertexData::~scVertexData()
{
}

void scVertexData::SetX(double x)
{
	mX = x;
}

void scVertexData::SetY(double y)
{
	mY = y;
}

double scVertexData::GetX() const
{
	return mX;
}

double scVertexData::GetY() const
{
	return mY;
}