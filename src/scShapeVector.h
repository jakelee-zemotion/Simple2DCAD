#pragma once
#include <vector>
#include <QDebug>
#include "scShape.h"
#include "scLine.h"
#include "scFace.h"


struct ClosedThreshold
{
	int minX, maxX;
	int minY, maxY;
};

class scShapeVector
{
public:
	scShapeVector() {};
	~scShapeVector() {};

	size_t size() const
	{
		return mShapes.size();
	}

	void DrawShape(QPainter& painter)
	{
		for (const auto& shape : mShapes)
		{
			shape->Paint(painter);
		}
	}

	void CreateNewLine(std::vector<QPoint> points)
	{
		mShapes.push_back(std::make_unique<scLine>(points));
	}

	void AddPointInLastShape(QPoint& point)
	{
		if (mShapes.empty())
			return;

		this->LastShapePointVec().push_back(point);
	}

	bool CloseTest(QPoint& currMousePos)
	{
		if (mShapes.empty() || this->LastShapePointVec().empty())
			return false;

		QPoint startPoint = this->LastShapePointVec().front();
		QPoint endPoint = currMousePos;
		if (IsObjectClosed(startPoint, endPoint))
		{
			qDebug() << "closed";

			// Remove two endPoints because drawPolygon() automatically connects the startPoint and endPoint.
			this->LastShapePointVec().pop_back();
			this->LastShapePointVec().pop_back();

			std::vector<QPoint> tempPoints = this->LastShapePointVec();

			// Remove the last shape(Line)
			mShapes.pop_back();

			// Create a new shape(Face)
			mShapes.push_back(std::make_unique<scFace>(tempPoints));

			return true;
		}

		return false;
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
		if (mShapes.empty() || this->LastShapePointVec().empty())
			return;

		// Remove adjusting point.
		this->LastShapePointVec().pop_back();

		// Put the shape in DrawObjects if its size is not 1. 
		// It is unnecessary to store a point.
		if (this->LastShapePointVec().size() <= 1)
		{
			mShapes.pop_back();
		}
	}

	void SetLastPoint(QPoint& point)
	{
		if (mShapes.empty() || this->LastShapePointVec().empty())
			return;

		this->LastShapePointVec().back() = point;
	}

	std::vector<std::shared_ptr<scShape>> mShapes;
private:
	ClosedThreshold mClosedThreshold = { 20, 20, 20, 20 };


	std::vector<QPoint>& LastShapePointVec()
	{
		return mShapes.back()->mPoints;
	}
};
