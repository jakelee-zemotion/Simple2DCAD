#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID();
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);

private:
	uint64_t mID;

	uint64_t GenerateID();
};

