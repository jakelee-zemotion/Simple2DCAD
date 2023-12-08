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
};

