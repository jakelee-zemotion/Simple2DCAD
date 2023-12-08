#include "scPolyLine.h"
#include "scQtLine.h"
#include "scQtVertex.h"


using namespace std;

scPolyline::scPolyline(shared_ptr<scQtLine>& firstLine)
{
	mSharedLineList = { firstLine };
	// mVertexList = 
}

scPolyline::~scPolyline()
{
}

void scPolyline::Paint(QPainter& painter)
{
	painter.drawPolyline(mVertexList);
}

void scPolyline::AddSharedLine(std::shared_ptr<scQtLine>& line)
{
	mSharedLineList.push_back(line);
	mVertexList.push_back(line->GetEndVertex());
}
