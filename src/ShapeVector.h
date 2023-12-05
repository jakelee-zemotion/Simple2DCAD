#pragma once
#include <vector>
#include <QDebug>
#include "Shape.h"
#include "Line.h"
#include "Face.h"

//using ShapeVector = std::vector<std::unique_ptr<Shape>>;


struct ClosedThreshold
{
	int minX, maxX;
	int minY, maxY;
};

// The reason for creating ShapeVector.
// 1. 
class ShapeVector
{
public:
	ShapeVector() {};
	~ShapeVector() {};

	size_t size()
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

	void CreateNewLine(QVector<QPoint> points)
	{
		mShapes.emplace_back(new Line(points));
	}

	void AddPointInLastShape(QPoint& point)
	{
		if (mShapes.empty())
			return;

		this->LastShapePointVec().push_back(point);
	}

	bool CloseTest(QPoint currMousePos)
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

			QVector<QPoint> tempPoints = this->LastShapePointVec();

			// Remove the last shape(Line)
			mShapes.pop_back();

			// Create a new shpae(Face)
			mShapes.emplace_back(new Face(tempPoints));

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
			this->LastShapePointVec().pop_back();
		}
	}

	void SetLastPoint(QPoint& point)
	{
		if (mShapes.empty() || this->LastShapePointVec().empty())
			return;

		this->LastShapePointVec().back() = point;
	}

private:
	std::vector<std::unique_ptr<Shape>> mShapes;
	ClosedThreshold mClosedThreshold = { 20, 20, 20, 20 };


	QVector<QPoint>& LastShapePointVec()
	{
		return mShapes.back()->mPoints;
	}
};
