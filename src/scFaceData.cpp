#include "scFaceData.h"

using namespace std;

scFaceData::scFaceData(const std::list<std::shared_ptr<scLineData>>& lineList)
	:mLineList(lineList)
{
	ResetIter();
}

scFaceData::~scFaceData()
{
}

size_t scFaceData::LineListSize() const
{
	return mLineList.size();
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

void scFaceData::SetLineStart(double startX, double startY)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->SetStartVertex(startX, startY);
}

void scFaceData::SetLineStartScale(double scaleX, double scaleY)
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	line->SetStartVertexScale(scaleX, scaleY);
}

double scFaceData::GetLineStartX() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartX();
}

double scFaceData::GetLineStartY() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartY();
}

double scFaceData::GetLineStartScaleX() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartScaleX();
}

double scFaceData::GetLineStartScaleY() const
{
	assert(mIter != mLineList.end());

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartScaleY();
}
