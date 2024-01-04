#pragma once

// system
#include <string>

class scShapeID
{
// [Member function section]
public:
	scShapeID(int id = -1);
	~scShapeID();

	std::string GenerateID();
	std::string ZeroPaddingStr(int id);

	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);
	operator std::string();

// [Memeber variable section]
private:
	std::string mID;

};

