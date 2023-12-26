#pragma once
#include "scMatrixVectorHelper.h"

#include <utility>

class scTransform
{
public:
	scTransform();
	~scTransform();

	scVector2D Scale(double x, double y) const;
	scVector2D UnScale(double x, double y) const;
	void MultiplyScaleXY(double scaleX, double scaleY);

	double GetScaleX() const;
	double GetScaleY() const;

private:
	double mScaleX;
	double mScaleY;

	double mRotateX;
	double mRotateY;

	scMatrix2D mScaleRotateMatrix;
	scMatrix2D mInverseScaleRotateMatrix;
};

