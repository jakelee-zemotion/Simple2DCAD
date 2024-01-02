#include "scShapeID.h"

scShapeID::scShapeID(int id)
{
	mID = id;

	if (id == -1)
	{
		mID = GenerateID();
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
