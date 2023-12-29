#pragma once
#include "scTransform.h"
#include "scMatrixVectorHelper.h"

class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void Add(const scVector2D& pos);
	void SetXY(const scVector2D& pos);

	scVector2D GetXY() const;
	scTransform& GetTransform();

private:
	scVector2D mPos;

	scTransform mTransform;
};

