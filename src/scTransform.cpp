#include "scTransform.h"

using namespace std;

scTransform::scTransform()
{
	mScaleX = 1.0;
	mScaleY = 1.0;

	mRotateX = 0.0;
	mRotateY = 0.0;

	mScaleRotateMatrix = MatrixHelper::IdentityMatrix();
	mInverseScaleRotateMatrix = MatrixHelper::IdentityMatrix();
}

scTransform::~scTransform()
{
}

scVector2D scTransform::Scale(double x, double y) const
{
	scVector2D r = { x, y };
	scVector2D result = mScaleRotateMatrix * r;

	return result;
}

scVector2D scTransform::UnScale(double x, double y) const
{
	scVector2D r = { x, y };
	scVector2D result = mInverseScaleRotateMatrix * r;

	return result;
}

void scTransform::MultiplyScaleXY(double scaleX, double scaleY)
{
	mScaleX *= scaleX;
	mScaleY *= scaleY;

	scMatrix2D nextScaleMatrix = MatrixHelper::ScaleMatrix(scaleX, scaleY);
	scMatrix2D nextInverseScaleMatrix = MatrixHelper::InverseScaleMatrix(scaleX, scaleY);

	mScaleRotateMatrix = (nextScaleMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseScaleMatrix);
}

double scTransform::GetScaleX() const
{
	return mScaleX;
}

double scTransform::GetScaleY() const
{
	return mScaleY;
}
