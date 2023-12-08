#pragma once

class scVertexInterface
{
public:
	virtual double GetX() const = 0;;
	virtual double GetY() const = 0;;

	virtual ~scVertexInterface() = 0 {};
};