#include "scShapeID.h"

using namespace std;

scShapeID::scShapeID(const int id)
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

scShapeID::operator std::string()
{
	return mID;
}

string scShapeID::GenerateID()
{
	static int id = 1;

	return ZeroPaddingStr(id++);
}

std::string scShapeID::ZeroPaddingStr(const int id)
{
	string idStr = to_string(id);
	reverse(idStr.begin(), idStr.end());

	string result = "000000000";

	for (int i = 0; i < idStr.size(); i++)
	{
		result[i] = idStr[i];
	}

	reverse(result.begin(), result.end());

	return result;
}
