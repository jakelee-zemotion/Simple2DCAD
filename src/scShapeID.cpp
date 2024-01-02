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

scShapeID::operator int() const
{
	return mID;
}

int scShapeID::GenerateID()
{
	static int id = 1;

	return id++;
}
