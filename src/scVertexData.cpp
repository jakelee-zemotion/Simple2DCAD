#include "scVertexData.h"

#include <qDebug>

scVertexData::scVertexData()
{
	mX = 0.0;
	mY = 0.0;
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

double scVertexData::GetX() const
{
	return mX;
}

double scVertexData::GetY() const
{
	return mY;
}