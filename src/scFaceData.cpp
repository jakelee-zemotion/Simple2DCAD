#include "scFaceData.h"

using namespace std;

scFaceData::scFaceData()
{
	shared_ptr<scVertexData> v1 = make_shared<scVertexData>();
	v1->SetX(100.0); v1->SetY(100.0);

	shared_ptr<scVertexData> v2 = make_shared<scVertexData>();
	v2->SetX(100.0); v2->SetY(200.0);

	shared_ptr<scVertexData> v3 = make_shared<scVertexData>();
	v3->SetX(200.0); v3->SetY(200.0);

	shared_ptr<scVertexData> v4 = make_shared<scVertexData>();
	v4->SetX(200.0); v4->SetY(100.0);

	shared_ptr<scLineData> line1 = make_shared<scLineData>();
	line1->SetStartVertex(v1); line1->SetEndVertex(v2);

	shared_ptr<scLineData> line2 = make_shared<scLineData>();
	line2->SetStartVertex(v2); line2->SetEndVertex(v3);

	shared_ptr<scLineData> line3 = make_shared<scLineData>();
	line3->SetStartVertex(v3); line3->SetEndVertex(v4);

	shared_ptr<scLineData> line4 = make_shared<scLineData>();
	line4->SetStartVertex(v4); line4->SetEndVertex(v1);

	mLineList.push_back(line1);
	mLineList.push_back(line2);
	mLineList.push_back(line3);
	mLineList.push_back(line4);

	mIter = mLineList.begin();
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
