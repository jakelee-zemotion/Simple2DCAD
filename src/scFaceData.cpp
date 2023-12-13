#include "scFaceData.h"

using namespace std;

scFaceData::scFaceData(const list<shared_ptr<scLineData>>& lineList)
	:mLineList(lineList)
{
}

scFaceData::~scFaceData()
{
}
