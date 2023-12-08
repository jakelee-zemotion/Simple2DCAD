#pragma once
#include <list>
#include <QDebug>
#include "scQtShapeInterface.h"
#include "scQtVertex.h"
#include "scQtLine.h"


struct ClosedThreshold
{
	int minX, maxX;
	int minY, maxY;
};

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
		//mShapeObjects.push_back(std::make_shared<scPolyline>(std::vector<QPoint>({ start, end })));

		// Copy the vertices.
		std::shared_ptr<scQtVertex> startVertex = std::make_shared<scQtVertex>(start);
		std::shared_ptr<scQtVertex> endVertex = std::make_shared<scQtVertex>(end);

		// Ref the vertices.
		std::shared_ptr<scQtLine> newLine = std::make_shared<scQtLine>(startVertex, endVertex);
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
		std::shared_ptr<scQtVertex>& startVertex = mVertexList.back();
		std::shared_ptr<scQtVertex> endVertex = std::make_shared<scQtVertex>(point);

		std::shared_ptr<scQtLine> newLine = std::make_shared<scQtLine>(startVertex, endVertex);
		//std::shared_ptr<scPolyline>& lastPolyline = mPolylineList.back();

		mVertexList.push_back(endVertex);
		mLineList.push_back(newLine);
		//lastPolyline->AddSharedLine(newLine);
	}

	bool CloseTest(QPointF& currMousePos)
	{
		//if (mShapeObjects.empty() || this->LastShapePointVec().empty())
		//	return false;

		//QPoint startPoint = this->LastShapePointVec().front();
		//QPoint endPoint = currMousePos;
		//if (IsObjectClosed(startPoint, endPoint))
		//{
		//	qDebug() << "closed";

		//	// Remove two endPoints because drawPolygon() automatically connects the startPoint and endPoint.
		//	this->LastShapePointVec().pop_back();
		//	this->LastShapePointVec().pop_back();

		//	std::vector<QPoint> tempPoints = this->LastShapePointVec();

		//	// Remove the last shape(Line)
		//	mShapeObjects.pop_back();

		//	// Create a new shape(Face)
		//	mShapeObjects.push_back(std::make_unique<scPolygon>(tempPoints));

		//	return true;
		//}

		//return false;
	}

	bool IsObjectClosed(QPointF& start, QPointF& end) const
	{
		if (start.x() - mClosedThreshold.minX < end.x()
			&& start.x() + mClosedThreshold.maxX > end.x()

			&& start.y() - mClosedThreshold.minY < end.y()
			&& start.y() + mClosedThreshold.maxY > end.y())
		{
			return true;
		}

		return false;
	}

	void CheckLastShape()
	{
		//if (mShapeObjects.empty() || this->LastShapePointVec().empty())
		//	return;

		//// Remove adjusting point.
		//this->LastShapePointVec().pop_back();

		//// Put the shape in DrawObjects if its size is not 1. 
		//// It is unnecessary to store a point.
		//if (this->LastShapePointVec().size() <= 1)
		//{
		//	mShapeObjects.pop_back();
		//}


	}

	void SetLastPoint(QPointF& point)
	{
		/*if (mShapeObjects.empty() || this->LastShapePointVec().empty())
			return;

		this->LastShapePointVec().back() = point;*/
	}

	//std::list<std::shared_ptr<scPolyline>> mPolylineList;
	//std::list<std::shared_ptr<scPolygon>> mPolygonList;
	std::list<std::shared_ptr<scQtLine>> mLineList;
	std::list<std::shared_ptr<scQtVertex>> mVertexList;



private:
	ClosedThreshold mClosedThreshold = { 20, 20, 20, 20 };


	
};
