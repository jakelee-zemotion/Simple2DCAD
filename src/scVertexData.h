#pragma once
class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void SetX(double x);
	void SetY(double y);

	void SetScaleX(double scaleX);
	void SetScaleY(double scaleY);

	void SetRotateX(double rotateX);
	void SetRotateY(double rotateY);

	double GetX() const;
	double GetY() const;

	double GetScaleX() const;
	double GetScaleY() const;

	double GetRotateX() const;
	double GetRotateY() const;

private:
	double mX;
	double mY;

	double mScaleX;
	double mScaleY;

	double mRotateX;
	double mRotateY;
};

