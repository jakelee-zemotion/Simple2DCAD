#pragma once
#include "scTransform.h"
#include "scMatrixVectorHelper.h"
#include "scShapeData.h"

class scVertexData : public scShapeData
{
public:
	scVertexData();
	~scVertexData() override;

	void AddDelta(const scVector2D& delta);
	void SetPos(const scVector2D& pos);

	scVector2D GetPos() const;
	scTransform& GetTransform();

private:
	scVector2D mPos;
	scTransform mTransform;
};

