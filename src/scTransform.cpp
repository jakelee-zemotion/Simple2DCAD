#include "scTransform.h"

using namespace std;

scTransform::scTransform()
{
	mScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
	mInverseScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
}

scVector2D scTransform::Scale(const scVector2D& pos) const
{
	return mScaleRotateMatrix * pos;
}

scVector2D scTransform::UnScale(const scVector2D& pos) const
{
	return mInverseScaleRotateMatrix * pos;
}

void scTransform::MultiplyScaleXY(const scVector2D& scale, const scVector2D& trans, const double angle)
{
	const scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(trans);
	const scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(trans);

	const scMatrix2D rotateMatrix = scMatrixHelper::RotateMatrix(angle);
	const scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(angle);

	const scMatrix2D scaleMatrix = scMatrixHelper::ScaleMatrix(scale);
	const scMatrix2D inverseScaleMatrix = scMatrixHelper::InverseScaleMatrix(scale);

	const scMatrix2D nextScaleMatrix = transMatrix * rotateMatrix * scaleMatrix * inverseRotateMatrix * inverseTransMatrix;
	const scMatrix2D nextInverseScaleMatrix = transMatrix * rotateMatrix * inverseScaleMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextScaleMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseScaleMatrix);
}

void scTransform::MultiplyRotateXY(const scVector2D& trans, const double angle)
{
	const scMatrix2D transMatrix = scMatrixHelper::TranslateMatrix(trans);
	const scMatrix2D inverseTransMatrix = scMatrixHelper::InverseTranslateMatrix(trans);

	const scMatrix2D rotateMatrix = scMatrixHelper::RotateMatrix(angle);
	const scMatrix2D inverseRotateMatrix = scMatrixHelper::InverseRotateMatrix(angle);

	const scMatrix2D nextRotateMatrix = transMatrix * rotateMatrix * inverseTransMatrix;
	const scMatrix2D nextInverseRotateMatrix = transMatrix * inverseRotateMatrix * inverseTransMatrix;

	mScaleRotateMatrix = (nextRotateMatrix * mScaleRotateMatrix);
	mInverseScaleRotateMatrix = (mInverseScaleRotateMatrix * nextInverseRotateMatrix);
}

void scTransform::ResetMatrix()
{
	mScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
	mInverseScaleRotateMatrix = scMatrixHelper::IdentityMatrix();
}
