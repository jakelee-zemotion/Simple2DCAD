#pragma once
class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void SetX(double x);
	void SetY(double y);

	void SetTransX(double transX);
	void SetTransY(double transY);

	double GetX() const;
	double GetY() const;

	double GetTransX() const;
	double GetTransY() const;

private:
	double mX;
	double mY;

	/*double mScaleX;
	double mScaleY;

	double mRotateX;
	double mRotateY;*/

	double mTransX;
	double mTransY;
};

