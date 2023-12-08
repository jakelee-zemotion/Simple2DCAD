#include "scPolyLine.h"
#include "scLine.h"
#include "scQtVertex.h"

using namespace std;

scPolyline::scPolyline(shared_ptr<scLine>& firstLine)
{
	mSharedLineList = { firstLine };
	// mVertexList = 
}

scPolyline::~scPolyline()
{
}

void scPolyline::Paint(QPainter& painter)
{
	/*QList<QPointF> vertices;
	
	vertices.push_back(mSharedLineList.front()->GetStartVertex());
	for (const auto& vertex : mSharedLineList)
	{
		vertices.push_back(vertex->GetEndVertex());
	}

	QPolygonF a(vertices);*/

	painter.drawPolyline(mVertexList);
	//painter.drawPolyline(mPoints.data(), mPoints.size());
}

void scPolyline::AddSharedLine(std::shared_ptr<scLine>& line)
{
	mSharedLineList.push_back(line);
	mVertexList.push_back(line->GetEndVertex());
}
