#pragma once

class scVertexVisualInterface
{
public:
	virtual double GetX() const = 0;
	virtual double GetY() const = 0;

	virtual void SetX(double x) = 0;
	virtual void SetY(double y) = 0;

	virtual ~scVertexVisualInterface() = 0 {};
};