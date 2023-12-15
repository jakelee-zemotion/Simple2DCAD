#pragma once
class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void SetX(double x);
	void SetY(double y);

	double GetX() const;
	double GetY() const;

private:
	double mX;
	double mY;

	double mScaleX;
	double mScaleY;

	double mRotateX;
	double mRotateY;

	double mTransX;
	double mTransY;
};

