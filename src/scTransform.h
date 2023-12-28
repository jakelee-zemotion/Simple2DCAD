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
	void MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY, double angle);
	void MultiplyRotateXY(double sinX, double cosX, double transX, double transY);

private:
	scMatrix2D mScaleRotateMatrix;
	scMatrix2D mInverseScaleRotateMatrix;
};

