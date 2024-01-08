#include "scGrid.h"

// qt
#include <QPainter>
#include <QDebug>

// Simple2DCAD
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scCoordinateHelper.h"
#include "scMatrixVectorHelper.h"
#include "scCamera.h"

using namespace std;

scGrid::scGrid(const shared_ptr<scCoordinateHelper>& coordinateHelper, const scCamera& camera, const QRect& viewportSize)
	:mCoordinateHelper(coordinateHelper), mCamera(camera), mViewportSize(viewportSize)
{
	mStride = 50.0;

	const int sizeX = mViewportSize.width() / mStride;
	const int sizeY = mViewportSize.height() / mStride;

	for (int i = 0; i < sizeX; i++)
	{
		mGridVertexList2D.push_back(list<shared_ptr<scVertexQtVisual>>());

		for (int j = 0; j < sizeY; j++)
		{
			const double x = i * mStride;
			const double y = j * mStride;
			const scVector2D start = { x,  y };

			const shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
			mGridVertexList2D.back().push_back(startVertex);
		}
	}
}

void scGrid::Paint(QPainter& painter)
{
	QPen pen;
	pen.setColor(Qt::gray);
	pen.setWidth(1);
	painter.setPen(pen);

	// Draw vertical lines.
	for (const auto& gridVertexDeque : mGridVertexList2D)
	{
		scVector2D startPos = gridVertexDeque.front()->GetXY();

		QPointF start = { startPos.x, 0.0 };
		QPointF end = { startPos.x, static_cast<double>(mViewportSize.height()) };

		painter.drawLine(start, end);
	}

	// Draw horizontal lines.
	for (const auto& gridVertex : mGridVertexList2D.front())
	{
		scVector2D startPos = gridVertex->GetXY();

		QPointF start = { 0.0, startPos.y };
		QPointF end = { static_cast<double>(mViewportSize.width()), startPos.y };

		painter.drawLine(start, end);
	}
}

std::shared_ptr<scShapeQtVisual> scGrid::HitTest(const scVector2D& currMousePos)
{
	for (const auto& gridVertexDeque : mGridVertexList2D)
	{
		for (const auto& gridVertex : gridVertexDeque)
		{
			if (gridVertex->HitTest(currMousePos))
			{
				return gridVertex;
			}
		}
	}

	return nullptr;
}


void scGrid::PanEvent()
{
	RemoveAddGridVertex();
}

void scGrid::ZoomEvent(int mouseDir)
{
	if (mouseDir > 0) // Zoom In
	{		
		ZoomInGrid();
	}
	else // Zoom Out
	{
		ZoomOutGrid();
	}

	RemoveAddGridVertex();
}

void scGrid::ZoomInGrid()
{
	mStride *= mCamera.GetZoomRatio();

	if (mStride > 100.0)
	{
		mStride /= 2.0;

		for (auto iterX = mGridVertexList2D.begin(); iterX != mGridVertexList2D.end(); iterX++)
		{
			std::list<std::shared_ptr<scVertexQtVisual>>& gridVertexDeque = *iterX;
			std::list<std::shared_ptr<scVertexQtVisual>> newGridVertexList;

			for (auto iter = gridVertexDeque.begin(); iter != gridVertexDeque.end(); iter++)
			{
				// Add a new GridVertex.
				const scVector2D pos = (*iter)->GetXY();
				scVector2D gridVertexPos = { pos.x, pos.y - mStride };
				shared_ptr<scVertexQtVisual> gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);

				gridVertexDeque.insert(iter, gridVertex);

				// Add new GridVertices to a new column.
				gridVertexPos = { pos.x - mStride, pos.y };
				scVector2D gridVertexPos2 = { pos.x - mStride, pos.y - mStride };
				gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);
				shared_ptr<scVertexQtVisual> gridVertex2 = make_shared<scVertexQtVisual>(gridVertexPos2, mCoordinateHelper);
				newGridVertexList.push_back(gridVertex2);
				newGridVertexList.push_back(gridVertex);
			}

			// Add a new column.
			mGridVertexList2D.insert(iterX, newGridVertexList);
		}
	}
}

void scGrid::ZoomOutGrid()
{
	mStride /= mCamera.GetZoomRatio();

	if (mStride < 50.0)
	{
		mStride *= 2.0;

		for (auto iterX = mGridVertexList2D.begin(); iterX != mGridVertexList2D.end();)
		{
			std::list<std::shared_ptr<scVertexQtVisual>>& gridVertexDeque = *iterX;

			auto iter = gridVertexDeque.begin();
			while (iter != gridVertexDeque.end())
			{
				iter++;
				if (iter == gridVertexDeque.end())
					break;

				// Remove the GridVertex
				iter = gridVertexDeque.erase(iter);

				if (iter == gridVertexDeque.end())
					break;
			}
			iterX++;

			if (iterX == mGridVertexList2D.end())
				break;

			// Remove the column.
			iterX = mGridVertexList2D.erase(iterX);
		}
	}
}

void scGrid::RemoveAddGridVertex()
{
	RemoveAddTopLeftGridVertex();
	RemoveAddBottomRightGridVertex();
}

void scGrid::RemoveAddTopLeftGridVertex()
{
	RemoveTopLeftGridVertex();
	AddTopLeftGridVertex();
}

void scGrid::RemoveTopLeftGridVertex()
{
	const double minX = 0.0;
	const double minY = 0.0;
	const double maxX = static_cast<double>(mViewportSize.width());
	const double maxY = static_cast<double>(mViewportSize.height());

	bool xFlag = true;
	bool yFlag = true;

	scVector2D topLeftPos = mGridVertexList2D.front().front()->GetXY();

	while (xFlag || yFlag)
	{
		xFlag = false;
		yFlag = false;
		topLeftPos = mGridVertexList2D.front().front()->GetXY();
		
		// Remove the GridVertex.
		if (topLeftPos.y < minY)
		{
			for (auto& gridVertexList : mGridVertexList2D)
			{
				gridVertexList.pop_front();
			}

			yFlag = true;
		}

		// Remove the column.
		if (topLeftPos.x < minX)
		{
			mGridVertexList2D.pop_front();

			xFlag = true;
		}
	}

}

void scGrid::AddTopLeftGridVertex()
{
	const double minX = 0.0;
	const double minY = 0.0;
	const double maxX = static_cast<double>(mViewportSize.width());
	const double maxY = static_cast<double>(mViewportSize.height());

	bool xFlag = true;
	bool yFlag = true;

	scVector2D topLeftPos = mGridVertexList2D.front().front()->GetXY();

	while (xFlag || yFlag)
	{
		xFlag = false;
		yFlag = false;
		topLeftPos = mGridVertexList2D.front().front()->GetXY();

		// Add a new column.
		if (topLeftPos.x - mStride >= minX)
		{
			std::list<std::shared_ptr<scVertexQtVisual>> newGridVertexList;

			for (int i = 0; i < mGridVertexList2D.front().size(); i++)
			{
				const scVector2D gridVertexPos = { topLeftPos.x - mStride, topLeftPos.y + i * mStride };
				const shared_ptr<scVertexQtVisual> gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);
				newGridVertexList.push_back(gridVertex);
			}

			mGridVertexList2D.push_front(newGridVertexList);

			xFlag = true;
		}

		topLeftPos = mGridVertexList2D.front().front()->GetXY();

		// Add new GridVertices.
		if (topLeftPos.y - mStride >= minY)
		{
			int i = 0;
			for (auto& gridVertexList : mGridVertexList2D)
			{
				const scVector2D gridVertexPos = { topLeftPos.x + i * mStride, topLeftPos.y - mStride };
				const shared_ptr<scVertexQtVisual> gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);
				gridVertexList.push_front(gridVertex);

				i++;
			}

			yFlag = true;
		}
	}
}

void scGrid::RemoveAddBottomRightGridVertex()
{
	RemoveBottomRightGridVertex();
	AddBottomRightGridVertex();
}

void scGrid::RemoveBottomRightGridVertex()
{
	const double minX = 0.0;
	const double minY = 0.0;
	const double maxX = static_cast<double>(mViewportSize.width());
	const double maxY = static_cast<double>(mViewportSize.height());

	bool xFlag = true;
	bool yFlag = true;

	scVector2D topLeftPos = mGridVertexList2D.front().front()->GetXY();
	scVector2D bottomRightPos = mGridVertexList2D.back().back()->GetXY();

	while (xFlag || yFlag)
	{
		xFlag = false;
		yFlag = false;

		bottomRightPos = mGridVertexList2D.back().back()->GetXY();

		// Remove the GridVertex.
		if (bottomRightPos.y > maxY)
		{
			for (auto& gridVertexList : mGridVertexList2D)
			{
				gridVertexList.pop_back();
			}

			yFlag = true;
		}

		// Remove the column.
		if (bottomRightPos.x > maxX)
		{
			mGridVertexList2D.pop_back();

			xFlag = true;
		}
	}
}

void scGrid::AddBottomRightGridVertex()
{
	const double minX = 0.0;
	const double minY = 0.0;
	const double maxX = static_cast<double>(mViewportSize.width());
	const double maxY = static_cast<double>(mViewportSize.height());

	bool xFlag = true;
	bool yFlag = true;

	scVector2D topLeftPos = mGridVertexList2D.front().front()->GetXY();
	scVector2D bottomRightPos = mGridVertexList2D.back().back()->GetXY();

	while (xFlag || yFlag)
	{
		xFlag = false;
		yFlag = false;

		bottomRightPos = mGridVertexList2D.back().back()->GetXY();

		// Add a new column.
		if (bottomRightPos.x + mStride <= maxX)
		{
			std::list<std::shared_ptr<scVertexQtVisual>> newGridVertexList;

			for (int i = 0; i < mGridVertexList2D.front().size(); i++)
			{
				const scVector2D gridVertexPos = { bottomRightPos.x + mStride, topLeftPos.y + i * mStride };
				const shared_ptr<scVertexQtVisual> gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);
				newGridVertexList.push_back(gridVertex);
			}

			mGridVertexList2D.push_back(newGridVertexList);

			xFlag = true;
		}

		bottomRightPos = mGridVertexList2D.back().back()->GetXY();

		// Add new GridVertices.
		if (bottomRightPos.y + mStride <= maxY)
		{
			int i = 0;
			for (auto& gridVertexList : mGridVertexList2D)
			{
				scVector2D gridVertexPos = { topLeftPos.x + i * mStride, bottomRightPos.y + mStride };
				shared_ptr<scVertexQtVisual> gridVertex = make_shared<scVertexQtVisual>(gridVertexPos, mCoordinateHelper);
				gridVertexList.push_back(gridVertex);

				i++;
			}

			yFlag = true;
		}
	}
}
