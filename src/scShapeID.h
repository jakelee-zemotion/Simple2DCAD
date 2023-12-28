#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID(bool IsInvalidID = true);
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);
	operator uint64_t() const;

private:
	uint64_t mID;

	uint64_t GenerateID();
};

