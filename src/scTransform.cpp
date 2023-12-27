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

void scTransform::MultiplyScaleXY(double scaleX, double scaleY, double transX, double transY, double angle)
{
	scMatrix2D transMatrix = MatrixHelper::TranslateMatrix(transX, transY);
	scMatrix2D inverseTransMatrix = MatrixHelper::InverseTranslateMatrix(transX, transY);

	scMatrix2D rotateMatrix = MatrixHelper::RotateMatrix(angle);
	scMatrix2D inverseRotateMatrix = MatrixHelper::InverseRotateMatrix(angle);

	scMatrix2D scaleMatrix = MatrixHelper::ScaleMatrix(scaleX, scaleY);
	scMatrix2D inverseScaleMatrix = MatrixHelper::InverseScaleMatrix(scaleX, scaleY);

	scMatrix2D nextScaleMatrix = transMatrix * rotateMatrix * scaleMatrix * inverseRotateMatrix * inverseTransMatrix;
	scMatrix2D nextInverseScaleMatrix = transMatrix * rotateMatrix * inverseScaleMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextScaleMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseScaleMatrix);
}

void scTransform::MultiplyRotateXY(double sinX, double cosX, double transX, double transY)
{
	scMatrix2D transMatrix = MatrixHelper::TranslateMatrix(transX, transY);
	scMatrix2D inverseTransMatrix = MatrixHelper::InverseTranslateMatrix(transX, transY);

	scMatrix2D rotateMatrix = MatrixHelper::RotateMatrix(sinX, cosX);
	scMatrix2D inverseRotateMatrix = MatrixHelper::InverseRotateMatrix(sinX, cosX);

	scMatrix2D nextRotateMatrix = transMatrix * rotateMatrix * inverseTransMatrix;
	scMatrix2D nextInverseRotateMatrix = transMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextRotateMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseRotateMatrix);

	angle += asin(sinX);
}
