#pragma once

// system
#include <string>

class scShapeID
{
public:
	scShapeID(int id = -1);
	~scShapeID();

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);

	operator std::string();

	std::string GenerateID();

	std::string ZeroPaddingStr(int id);

private:
	std::string mID;

};

