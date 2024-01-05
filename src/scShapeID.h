#pragma once

// system
#include <string>

class scShapeID
{
// [Member function section]
public:
	scShapeID(const int id = -1);
	~scShapeID();

	std::string GenerateID();
	std::string ZeroPaddingStr(const int id);

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);
	operator std::string();

// [Member variable section]
private:
	std::string mID;

};

