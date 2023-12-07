#include "scPolyLine.h"

using namespace std;

scPolyline::scPolyline(shared_ptr<scLine>& firstLine)
{
	mSharedLineList = { firstLine };
}

scPolyline::~scPolyline()
{
}

void scPolyline::Paint(QPainter& painter)
{
	list<QPointF> vertices;
	
	//vertices.push_back(mSharedLineList.front());
	for (const auto& vertex : mSharedLineList)
	{

	}


	//painter.drawPolyline()
	//painter.drawPolyline(mPoints.data(), mPoints.size());
}
