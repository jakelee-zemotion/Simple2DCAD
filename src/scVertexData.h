#pragma once
#include "scTransform.h"

class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void SetX(double x);
	void SetY(double y);

	double GetX() const;
	double GetY() const;

	scTransform& GetTransform();

private:
	double mX;
	double mY;

	scTransform mTransform;
};

