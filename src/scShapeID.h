#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID();
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);

	uint64_t Get();

private:
	uint64_t mID;

	uint64_t GenerateID();
};

