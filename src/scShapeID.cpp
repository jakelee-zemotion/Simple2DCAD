#include "scShapeID.h"

scShapeID::scShapeID(bool IsInvalidID)
{
	mID = 0;

	if (IsInvalidID)
	{
		mID = this->GenerateID();
	}

}

scShapeID::~scShapeID()
{
}

bool scShapeID::operator==(const scShapeID& shapeID)
{
	return mID == shapeID.mID;
}

bool scShapeID::operator!=(const scShapeID& shapeID)
{
	return mID != shapeID.mID;
}

uint64_t scShapeID::Get() const
{
	return mID;
}


uint64_t scShapeID::GenerateID()
{
	static uint64_t id = 1;

	return id++;
}
