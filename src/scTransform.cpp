#include "scTransform.h"

using namespace std;

scTransform::scTransform()
{
	mScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
	mInverseScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
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

void scTransform::MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY, double angle)
{
	scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(transX, transY);
	scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(transX, transY);

	scMatrix2D rotateMatrix = scMatrixHelper::RotateMatrix(angle);
	scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(angle);

	scMatrix2D scaleMatrix = scMatrixHelper::ScaleMatrix(scaleX, scaleY);
	scMatrix2D inverseScaleMatrix = scMatrixHelper::InverseScaleMatrix(scaleX, scaleY);

	scMatrix2D nextScaleMatrix = transMatrix * rotateMatrix * scaleMatrix * inverseRotateMatrix * inverseTransMatrix;
	scMatrix2D nextInverseScaleMatrix = transMatrix * rotateMatrix * inverseScaleMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextScaleMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseScaleMatrix);
}

void scTransform::MultiplyRotateXY(double angle, double transX, double transY)
{
	scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(transX, transY);
	scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(transX, transY);

	scMatrix2D rotateMatrix = scMatrixHelper::RotateMatrix(angle);
	scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(angle);

	scMatrix2D nextRotateMatrix = transMatrix * rotateMatrix * inverseTransMatrix;
	scMatrix2D nextInverseRotateMatrix = transMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextRotateMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseRotateMatrix);
}

void scTransform::ResetMatrix()
{
	mScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
	mInverseScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
}
