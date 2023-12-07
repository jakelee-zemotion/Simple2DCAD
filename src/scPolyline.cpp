#include "scPolyLine.h"
#include "scLine.h"

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
	QList<QPointF> vertices;
	
	vertices.push_back(mSharedLineList.front()->GetStartVertex());
	for (const auto& vertex : mSharedLineList)
	{
		vertices.push_back(vertex->GetEndVertex());
	}

	QPolygonF a(vertices);

	painter.drawPolyline(a);
	//painter.drawPolyline(mPoints.data(), mPoints.size());
}

void scPolyline::AddSharedLine(std::shared_ptr<scLine>& line)
{
	mSharedLineList.push_back(line);
}
