#pragma once
#include "scLineData.h"

#include <list>
#include <memory>

class scFaceData
{
public:
	scFaceData();
	~scFaceData();

	size_t LineListSize() const;

	void ResetIter();
	void NextIter();
	bool IsIterEnd();

	/*void SetLineStartEnd(
		double startX, double startY, 
		double endX, double endY);*/

	double GetLineStartX() const;
	double GetLineStartY() const;
	double GetLineEndX() const;
	double GetLineEndY() const;

private:
	std::list<std::shared_ptr<scLineData>> mLineList;
	std::list<std::shared_ptr<scLineData>>::iterator mIter;
};

