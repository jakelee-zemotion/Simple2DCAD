#pragma once
#include "scLineData.h"

#include <list>
#include <memory>
#include <cassert>

class scFaceData
{
public:
	scFaceData();
	~scFaceData();

	void AddLineData(const std::shared_ptr<scLineData>& lineData);

	void ResetIter();
	void NextIter();
	bool IsIterEnd();

	void AddDxDyToLineStart(double dx, double dy);
	void SetLineStart(double startX, double startY);

	double GetLineStartX() const;
	double GetLineStartY() const;
	scTransform& GetStartTransform();

private:
	std::list<std::shared_ptr<scLineData>> mLineList;
	std::list<std::shared_ptr<scLineData>>::iterator mIter;
};

