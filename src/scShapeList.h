#pragma once
#include <list>
#include <QDebug>
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"


class scShapeList
{
public:
	scShapeList() {};
	~scShapeList() {};

	size_t size() const
	{
		return 1;//mPolygonList.size();
	}

	void DrawShape(QPainter& painter)
	{
		for (const auto& shape : mLineList)
		{
			shape->Paint(painter);
		}

		for (const auto& shape : mVertexList)
		{
			shape->Paint(painter);
		}
	}

	void AddLine(QPointF& start, QPointF& end)
	{
		// Copy the vertices.
		std::shared_ptr<scVertexQtVisual> startVertex = std::make_shared<scVertexQtVisual>(start);
		std::shared_ptr<scVertexQtVisual> endVertex = std::make_shared<scVertexQtVisual>(end);

		// Ref the vertices.
		std::shared_ptr<scLineQtVisual> newLine = std::make_shared<scLineQtVisual>(startVertex, endVertex);
		//std::shared_ptr<scPolyline> newPolyline = std::make_shared<scPolyline>(newLine);

		// Add Vertices.
		mVertexList.push_back(startVertex);
		mVertexList.push_back(endVertex);

		// Add a new line and ployline.
		mLineList.push_back(newLine);
		//mPolylineList.push_back(newPolyline);
	}

	void AddVertex(QPointF& point)
	{
		/*if (mShapeObjects.empty())
			return;

		this->LastShapePointVec().push_back(point);*/

		// Ref and Copy vertex.
		std::shared_ptr<scVertexQtVisual>& startVertex = mVertexList.back();
		std::shared_ptr<scVertexQtVisual> endVertex = std::make_shared<scVertexQtVisual>(point);

		std::shared_ptr<scLineQtVisual> newLine = std::make_shared<scLineQtVisual>(startVertex, endVertex);
		//std::shared_ptr<scPolyline>& lastPolyline = mPolylineList.back();

		mVertexList.push_back(endVertex);
		mLineList.push_back(newLine);
		//lastPolyline->AddSharedLine(newLine);
	}
	

	void EndDrawing()
	{
		if (mVertexList.empty() || mLineList.empty())
			return;

		mVertexList.pop_back();
		mLineList.pop_back();

	}

	void MoveDrawingPoint(QPointF& point)
	{
		if (mVertexList.empty())
			return;

		std::shared_ptr<scVertexQtVisual> lastVertex = mVertexList.back();

		lastVertex->SetX(point.x());
		lastVertex->SetY(point.y());
	}

	std::list<std::shared_ptr<scLineQtVisual>> mLineList;
	std::list<std::shared_ptr<scVertexQtVisual>> mVertexList;



private:
	
};
