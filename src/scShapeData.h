#pragma once
#include "scShapeID.h"

class scShapeData
{
public:
	scShapeData();
	virtual ~scShapeData();

	scShapeID GetID() const;

private:
	const scShapeID mShapeID;
};

