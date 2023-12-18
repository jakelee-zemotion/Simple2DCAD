#include "scVertexData.h"

#include <qDebug>

scVertexData::scVertexData()
{
	mX = 0.0;
	mY = 0.0;

	mScaleX = 0.0;
	mScaleY = 0.0;

	mRotateX = 0.0;
	mRotateY = 0.0;
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

void scVertexData::SetScaleX(double scaleX)
{
	mScaleX = scaleX;
}

void scVertexData::SetScaleY(double scaleY)
{
	mScaleY = scaleY;
}

void scVertexData::SetRotateX(double rotateX)
{
	mRotateX = rotateX;
}

void scVertexData::SetRotateY(double rotateY)
{
	mRotateY = rotateY;
}

double scVertexData::GetX() const
{
	return mX;
}

double scVertexData::GetY() const
{
	return mY;
}

double scVertexData::GetScaleX() const
{
	return mScaleX;
}

double scVertexData::GetScaleY() const
{
	return mScaleY;
}

double scVertexData::GetRotateX() const
{
	return mRotateX;
}

double scVertexData::GetRotateY() const
{
	return mRotateY;
}
