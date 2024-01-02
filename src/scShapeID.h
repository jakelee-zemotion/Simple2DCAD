#pragma once
#include <cstdint>

class scShapeID
{
public:
	scShapeID(int id = -1);
	~scShapeID();


	bool operator==(const scShapeID& shapeID);
	bool operator!=(const scShapeID& shapeID);
	operator int() const;

	static int GenerateID();

private:
	int mID;

};

