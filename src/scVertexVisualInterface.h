#pragma once

class scVertexVisualInterface
{
public:
	virtual double GetX() const = 0;
	virtual double GetY() const = 0;

	virtual ~scVertexVisualInterface() = 0 {};
};