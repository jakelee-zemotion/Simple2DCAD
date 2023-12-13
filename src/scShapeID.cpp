#include "scShapeID.h"

scShapeID::scShapeID()
{
	mID = this->GenerateID();
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


uint64_t scShapeID::GenerateID()
{
	static uint64_t id = 0;

	return id++;
}
