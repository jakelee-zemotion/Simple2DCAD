#include "scTransform.h"

using namespace std;

scTransform::scTransform()
{
	mScaleX = 1.0;
	mScaleY = 1.0;

	mRotateX = 0.0;
	mRotateY = 0.0;
}

scTransform::~scTransform()
{
}

pair<double, double> scTransform::Scale(double x, double y) const
{
	x *= mScaleX;
	y *= mScaleY;

	return { x, y };
}

std::pair<double, double> scTransform::UnScale(double x, double y) const
{
	x /= mScaleX;
	y /= mScaleY;

	return { x, y };
}

void scTransform::MultiplyScaleXY(double scaleX, double scaleY)
{
	mScaleX *= scaleX;
	mScaleY *= scaleY;
}

double scTransform::GetScaleX() const
{
	return mScaleX;
}

double scTransform::GetScaleY() const
{
	return mScaleY;
}
