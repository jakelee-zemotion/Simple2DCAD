#pragma once

// Simple2DCAD
#include "scShapeID.h"

class scShapeData
{
// [Member function section]
public:
	scShapeData();
	virtual ~scShapeData();

	scShapeID GetID() const;

// [Member variable section]
private:
	const scShapeID mShapeID;
};

