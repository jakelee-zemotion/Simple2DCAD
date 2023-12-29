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

void scFaceData::AddDxDyToLineStart(double dx, double dy)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->AddDeltaToStart({ dx, dy });
}

void scFaceData::SetLineStart(double startX, double startY)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->SetPosToStartVertex({ startX, startY });
}

double scFaceData::GetLineStartX() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartPos().x;
}

double scFaceData::GetLineStartY() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartPos().y;
}

scTransform& scFaceData::GetStartTransform()
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartTransform();
}