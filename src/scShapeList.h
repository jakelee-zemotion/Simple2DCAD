#pragma once
#include <list>
#include <QDebug>
#include "scShapeInterface.h"
#include "scVertex.h"
#include "scLine.h"
#include "scPolygon.h"
#include "scPolyline.h"


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
		return mShapeObjects.size();
	}

	void DrawShape(QPainter& painter)
	{
		for (const auto& shape : mShapeObjects)
		{
			shape->Paint(painter);
		}
	}

	void CreateNewLine(QPoint& start, QPoint& end)
	{
		//mShapeObjects.push_back(std::make_shared<scPolyline>(std::vector<QPoint>({ start, end })));

		std::shared_ptr<scVertex> startVertex = std::make_shared<scVertex>(start);
		std::shared_ptr<scVertex> endVertex = std::make_shared<scVertex>(end);
		std::shared_ptr<scLine> newLine = std::make_shared<scLine>(startVertex, endVertex);
		//std::shared_ptr<scPolyline> newPolyline = std::make_shared<scLine>(newLine);


		mVertexList.push_back(startVertex);
		mVertexList.push_back(endVertex);

		mLineList.push_back(std::make_shared<scLine>(startVertex, endVertex));
		//mPolylineList.push_back(std::make_shared<scLine>())
	}

	void AddPointInLastShape(QPoint& point)
	{
		/*if (mShapeObjects.empty())
			return;

		this->LastShapePointVec().push_back(point);*/


		std::shared_ptr<scVertex>& startVertex = mVertexList.back();
		std::shared_ptr<scVertex> endVertex = std::make_shared<scVertex>(point);
		mVertexList.push_back(endVertex);

		mLineList.push_back(std::make_shared<scLine>(startVertex, endVertex));

	}

	bool CloseTest(QPoint& currMousePos)
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

	bool IsObjectClosed(QPoint& start, QPoint& end) const
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
		if (mShapeObjects.empty() || this->LastShapePointVec().empty())
			return;

		// Remove adjusting point.
		this->LastShapePointVec().pop_back();

		// Put the shape in DrawObjects if its size is not 1. 
		// It is unnecessary to store a point.
		if (this->LastShapePointVec().size() <= 1)
		{
			mShapeObjects.pop_back();
		}


	}

	void SetLastPoint(QPoint& point)
	{
		if (mShapeObjects.empty() || this->LastShapePointVec().empty())
			return;

		this->LastShapePointVec().back() = point;
	}

	std::list<std::shared_ptr<scShapeInterface>> mShapeObjects;
	std::list<std::shared_ptr<scPolyline>> mPolylineList;
	std::list<std::shared_ptr<scPolygon>> mPolygonList;
	std::list<std::shared_ptr<scLine>> mLineList;
	std::list<std::shared_ptr<scVertex>> mVertexList;


private:
	ClosedThreshold mClosedThreshold = { 20, 20, 20, 20 };


	std::vector<QPoint>& LastShapePointVec()
	{
		return mShapeObjects.back()->mPoints;
	}
};
