#include "scGrid.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scCoordinateHelper.h"
#include "scMatrixVectorHelper.h"
#include "scCamera.h"

#include <QPainter>
#include <QDebug>

using namespace std;

scGrid::scGrid(
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper, 
	const scCamera& camera, 
	const QRect& viewportSize)
		:mCoordinateHelper(coordinateHelper), mCamera(camera), mViewportSize(viewportSize)
{
	int sizeX = mViewportSize.width() / mStride;
	int sizeY = mViewportSize.height() / mStride;

	mGridVertexDeque2D = deque<deque<shared_ptr<scVertexQtVisual>>>(sizeX, deque<shared_ptr<scVertexQtVisual>>(sizeY));

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			double x = i * mStride;
			double y = j * mStride;

			scVector2D start = { x,  y };

			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
			mGridVertexDeque2D[i][j] = startVertex;
		}
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	for (int i = 0; i < mGridVertexDeque2D.size(); i ++)
	{
		for (int j = 0; j < mGridVertexDeque2D[i].size(); j ++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque2D[i][j];

			vertex->Paint(painter);
		}
	}
}

std::shared_ptr<scShapeQtVisual> scGrid::HitTest(const scVector2D& currMousePos)
{
	for (int i = 0; i < mGridVertexDeque2D.size(); i++)
	{
		for (int j = 0; j < mGridVertexDeque2D[i].size(); j++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque2D[i][j];

			if (vertex->HitTest(currMousePos))
			{
				return vertex;
			}
		}
	}

	return nullptr;
}


void scGrid::PanEvent()
{
	AddRemoveGridVertex();

}

void scGrid::ZoomEvent(int mouseDir)
{
	if (mouseDir > 0) // Zoom In
	{
		mStride *= mCamera.GetZoomRatio();
	}
	else // Zoom Out
	{
		mStride /= mCamera.GetZoomRatio();
	}

	AddRemoveGridVertex();
}

void scGrid::AddRemoveGridVertex()
{
	double minX = 0.0;
	double minY = 0.0;
	double maxX = static_cast<double>(mViewportSize.width());
	double maxY = static_cast<double>(mViewportSize.height());

	bool xFlag;
	bool yFlag;

	// ######### topLeft ##########
	scVector2D topLeftPos;

	// Remove
	do
	{
		xFlag = false;
		yFlag = false;
		topLeftPos = mGridVertexDeque2D.front().front()->GetXY();

		if (topLeftPos.y < minY)
		{
			for (int i = 0; i < mGridVertexDeque2D.size(); i++)
			{
				mGridVertexDeque2D[i].pop_front();
			}

			yFlag = true;
		}

		if (topLeftPos.x < minX)
		{
			mGridVertexDeque2D.pop_front();

			xFlag = true;
		}
	} while (xFlag || yFlag);


	// Add
	do
	{
		xFlag = false;
		yFlag = false;

		topLeftPos = mGridVertexDeque2D.front().front()->GetXY();

		if (topLeftPos.x - mStride >= minX)
		{
			std::deque<std::shared_ptr<scVertexQtVisual>> newGridVertexDeque;

			for (int i = 0; i < mGridVertexDeque2D[0].size(); i++)
			{
				scVector2D start = { topLeftPos.x - mStride, topLeftPos.y + i * mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				newGridVertexDeque.push_back(startVertex);
			}

			mGridVertexDeque2D.push_front(newGridVertexDeque);

			xFlag = true;
		}

		topLeftPos = mGridVertexDeque2D.front().front()->GetXY();
		if (topLeftPos.y - mStride >= minY)
		{
			for (int i = 0; i < mGridVertexDeque2D.size(); i++)
			{
				scVector2D start = { topLeftPos.x + i * mStride, topLeftPos.y - mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				mGridVertexDeque2D[i].push_front(startVertex);
			}

			yFlag = true;
		}


	} while (xFlag || yFlag);



	// ######### bottomRight ##########
	topLeftPos = mGridVertexDeque2D.front().front()->GetXY();
	scVector2D bottomRightPos;

	do
	{
		xFlag = false;
		yFlag = false;

		bottomRightPos = mGridVertexDeque2D.back().back()->GetXY();

		// Remove
		if (bottomRightPos.y > maxY)
		{
			for (int i = 0; i < mGridVertexDeque2D.size(); i++)
			{
				mGridVertexDeque2D[i].pop_back();
			}

			yFlag = true;
		}

		if (bottomRightPos.x > maxX)
		{
			mGridVertexDeque2D.pop_back();

			xFlag = true;
		}
	} while (xFlag || yFlag);


	do
	{
		xFlag = false;
		yFlag = false;

		// Add
		bottomRightPos = mGridVertexDeque2D.back().back()->GetXY();
		if (bottomRightPos.x + mStride <= maxX)
		{
			std::deque<std::shared_ptr<scVertexQtVisual>> newGridVertexDeque;

			for (int i = 0; i < mGridVertexDeque2D[0].size(); i++)
			{
				scVector2D start = { bottomRightPos.x + mStride, topLeftPos.y + i * mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				newGridVertexDeque.push_back(startVertex);
			}

			mGridVertexDeque2D.push_back(newGridVertexDeque);

			xFlag = true;
		}

		bottomRightPos = mGridVertexDeque2D.back().back()->GetXY();
		if (bottomRightPos.y + mStride <= maxY)
		{
			for (int i = 0; i < mGridVertexDeque2D.size(); i++)
			{
				scVector2D start = { topLeftPos.x + i * mStride, bottomRightPos.y + mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				mGridVertexDeque2D[i].push_back(startVertex);
			}

			yFlag = true;
		}
	} while (xFlag || yFlag);

}
