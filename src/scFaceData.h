#pragma once

// system
#include <list>
#include <memory>
#include <cassert>

// Simple2DCAD
#include "scLineData.h"
#include "scShapeData.h"

class scFaceData : public scShapeData
{
// [Member function section]
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
	scTransform& GetLineStartTransform();
	scShapeID GetLineStartID() const;

// [Member variable section]
private:
	std::list<std::shared_ptr<scLineData>> mLineList;
	std::list<std::shared_ptr<scLineData>>::iterator mIter;
};

