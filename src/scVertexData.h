#pragma once
#include "scTransform.h"
#include "scMatrixVectorHelper.h"

class scVertexData
{
public:
	scVertexData();
	~scVertexData();

	void AddDelta(const scVector2D& delta);
	void SetPos(const scVector2D& pos);

	scVector2D GetPos() const;
	scTransform& GetTransform();

private:
	scVector2D mPos;

	scTransform mTransform;
};

