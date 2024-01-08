#pragma once

// Simple2DCAD
#include "scTransform.h"
#include "scMatrixVectorHelper.h"
#include "scShapeData.h"

class scVertexData : public scShapeData
{
// [Member function section]
public:
	scVertexData();

	void AddDelta(const scVector2D& delta);
	void SetPos(const scVector2D& pos);

	scVector2D GetPos() const;
	scTransform& GetTransform();

// [Member variable section]
private:
	scVector2D mPos;
	scTransform mTransform;
};

