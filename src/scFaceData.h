#pragma once
#include "scLineData.h"

#include <list>
#include <memory>

class scFaceData
{
public:
	scFaceData(const std::list<std::shared_ptr<scLineData>>& lineList);
	~scFaceData();

private:
	std::list<std::shared_ptr<scLineData>> mLineList;
};

