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
	if (mIter == mLineList.end())
		return;

	mIter++;
}

bool scFaceData::IsIterEnd()
{
	return mIter == mLineList.end();
}

double scFaceData::GetLineStartX() const
{
	if (mIter == mLineList.end())
		return 0.0;

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartX();
}

double scFaceData::GetLineStartY() const
{
	if (mIter == mLineList.end())
		return 0.0;

	shared_ptr<scLineData>& line = *mIter;
	return line->GetStartY();
}

double scFaceData::GetLineEndX() const
{
	if (mIter == mLineList.end())
		return 0.0;

	shared_ptr<scLineData>& line = *mIter;
	return line->GetEndX();
}

double scFaceData::GetLineEndY() const
{
	if (mIter == mLineList.end())
		return 0.0;

	shared_ptr<scLineData>& line = *mIter;
	return line->GetEndY();
}

//void scFaceData::SetLineStartEnd(double startX, double startY, double endX, double endY)
//{
//	shared_ptr<scLineData>& line = *mIter;
//	line->SetStartVertex(startX, startY);
//	line->SetEndVertex(endX, endY);
//}
