#include "scTransform.h"

using namespace std;

scTransform::scTransform()
{
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

void scTransform::MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY)
{
	scMatrix2D transMatrix = MatrixHelper::TranslateMatrix(transX, transY);
	scMatrix2D inverseTransMatrix = MatrixHelper::InverseTranslateMatrix(transX, transY);

	scMatrix2D scaleMatrix = MatrixHelper::ScaleMatrix(scaleX, scaleY);
	scMatrix2D inverseScaleMatrix = MatrixHelper::InverseScaleMatrix(scaleX, scaleY);

	scMatrix2D nextScaleMatrix = transMatrix * scaleMatrix * inverseTransMatrix;
	scMatrix2D nextInverseScaleMatrix = transMatrix * inverseScaleMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextScaleMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseScaleMatrix);
}