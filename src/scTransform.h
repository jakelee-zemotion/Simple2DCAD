#pragma once

// system
#include <utility>

// Simple2DCAD
#include "scMatrixVectorHelper.h"

class scTransform
{
// [Member function section]
public:
	scTransform();

	scVector2D Scale(const scVector2D& pos) const;
	scVector2D UnScale(const scVector2D& pos) const;
	void MultiplyScaleXY(const scVector2D& scale, const scVector2D& trans, const double angle);
	void MultiplyRotateXY(const scVector2D& trans, const double angle);

	void ResetMatrix();

// [Member variable section]
private:
	scMatrix2D mScaleRotateMatrix;
	scMatrix2D mInverseScaleRotateMatrix;
};

