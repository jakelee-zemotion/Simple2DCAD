#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID(bool IsInvalidID = true);
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);

	uint64_t Get() const;

private:
	uint64_t mID;

	uint64_t GenerateID();
};

