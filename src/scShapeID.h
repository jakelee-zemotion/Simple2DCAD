#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID(bool IsInvalidID = true);
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);
	operator int() const;

private:
	int mID;

	int GenerateID();
};

