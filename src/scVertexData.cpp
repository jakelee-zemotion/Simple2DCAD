#include "scVertexData.h"

#include <qDebug>

scVertexData::scVertexData()
{
	mX = 0.0;
	mY = 0.0;

	mTransX = 0.0;
	mTransY = 0.0;
}

scVertexData::~scVertexData()
{
	//qDebug() << "VertexData Destruction";
}

void scVertexData::SetX(double x)
{
	mX = x;
}

void scVertexData::SetY(double y)
{
	mY = y;
}

void scVertexData::SetTransX(double transX)
{
	mTransX = transX;
}

void scVertexData::SetTransY(double transY)
{
	mTransY = transY;
}

double scVertexData::GetX() const
{
	return mX;
}

double scVertexData::GetY() const
{
	return mY;
}

double scVertexData::GetTransX() const
{
	return mTransX;
}

double scVertexData::GetTransY() const
{
	return mTransY;
}
