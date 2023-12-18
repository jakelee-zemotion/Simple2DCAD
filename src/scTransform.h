#pragma once
#include <utility>

class scTransform
{
public:
	scTransform();
	~scTransform();

	std::pair<double, double> Scale(double x, double y) const;
	std::pair<double, double> UnScale(double x, double y) const;
	void MultiplyScaleXY(double scaleX, double scaleY);

	double GetScaleX() const;
	double GetScaleY() const;

private:
	double mScaleX;
	double mScaleY;

	double mRotateX;
	double mRotateY;
};

