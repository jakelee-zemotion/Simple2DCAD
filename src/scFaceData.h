#pragma once
#include "scLineData.h"
#include "scShapeData.h"

#include <list>
#include <memory>
#include <cassert>

class scFaceData : public scShapeData
{
public:
	scFaceData();
	~scFaceData() override;

	void AddLineData(const std::shared_ptr<scLineData>& lineData);

	void ResetIter();
	void NextIter();
	bool IsIterEnd();

	void AddDeltaToLineStart(const scVector2D& delta);
	void SetLineStartPos(const scVector2D& pos);

	scVector2D GetLineStartPos() const;
	scTransform& GetStartTransform();

private:
	std::list<std::shared_ptr<scLineData>> mLineList;
	std::list<std::shared_ptr<scLineData>>::iterator mIter;
};

