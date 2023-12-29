#include "scFaceData.h"

using namespace std;

scFaceData::scFaceData()
{
	ResetIter();
}

scFaceData::~scFaceData()
{
}

void scFaceData::AddLineData(const std::shared_ptr<scLineData>& lineData)
{
	mLineList.push_back(lineData);
}

void scFaceData::ResetIter()
{
	mIter = mLineList.begin();
}

void scFaceData::NextIter()
{
	assert(mIter != mLineList.end());

	mIter++;
}

bool scFaceData::IsIterEnd()
{
	return mIter == mLineList.end();
}

void scFaceData::AddDeltaToLineStart(const scVector2D& delta)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->AddDeltaToStart(delta);
}

void scFaceData::SetLineStartPos(const scVector2D& pos)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->SetPosToStartVertex(pos);
}

scVector2D scFaceData::GetLineStartPos() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartPos();
}

scTransform& scFaceData::GetStartTransform()
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartTransform();
}