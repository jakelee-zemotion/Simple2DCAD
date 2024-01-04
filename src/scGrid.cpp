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

	//mGridVertexList2D = deque<deque<shared_ptr<scVertexQtVisual>>>(sizeX, deque<shared_ptr<scVertexQtVisual>>(sizeY));

	for (int i = 0; i < sizeX; i++)
	{
		mGridVertexList2D.push_back(list<shared_ptr<scVertexQtVisual>>());

		for (int j = 0; j < sizeY; j++)
		{
			double x = i * mStride;
			double y = j * mStride;

			scVector2D start = { x,  y };

			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
			mGridVertexList2D.back().push_back(startVertex);
		}
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	for (const auto& gridVertexDeque : mGridVertexList2D)
	{
		for (const auto& gridVertex : gridVertexDeque)
		{
			gridVertex->Paint(painter);
		}
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
	AddRemoveGridVertex();

}

void scGrid::ZoomEvent(int mouseDir)
{
	if (mouseDir > 0) // Zoom In
	{
		mStride *= mCamera.GetZoomRatio();

		//if (mStride > 100.0)
		//{
		//	mStride /= 2.0;

		//	for (int i = 0; i < mGridVertexList2D.size(); i++)
		//	{
		//		for (int j = 0; j < mGridVertexList2D[i].size(); j += 2)
		//		{
		//			scVector2D pos = mGridVertexList2D[i][j]->GetXY();

		//			scVector2D start = { pos.x, pos.y + (j + 1) * mStride };
		//			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);

		//			int cnt = j;
		//			auto iter = mGridVertexList2D[i].begin();
		//			iter++;
		//			while (cnt--)
		//				iter++;



		//			mGridVertexList2D[i].insert(iter, startVertex);

		//			int  k = 0;
		//		}


		//		/*std::deque<std::shared_ptr<scVertexQtVisual>> newGridVertexDeque;
		//		for (int j = 0; j < mGridVertexList2D[i].size(); j++)
		//		{
		//			scVector2D start = { topLeftPos.x - mStride, topLeftPos.y + i * mStride };
		//			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
		//			newGridVertexDeque.push_back(startVertex);
		//		}*/
		//	}
		//}
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
		topLeftPos = mGridVertexList2D.front().front()->GetXY();

		if (topLeftPos.y < minY)
		{
			for (auto& gridVertexDeque : mGridVertexList2D)
			{
				gridVertexDeque.pop_front();
			}

			yFlag = true;
		}

		if (topLeftPos.x < minX)
		{
			mGridVertexList2D.pop_front();

			xFlag = true;
		}
	} while (xFlag || yFlag);


	// Add
	do
	{
		xFlag = false;
		yFlag = false;

		topLeftPos = mGridVertexList2D.front().front()->GetXY();

		if (topLeftPos.x - mStride >= minX)
		{
			std::list<std::shared_ptr<scVertexQtVisual>> newGridVertexDeque;

			for (int i = 0; i < mGridVertexList2D.front().size(); i++)
			{
				scVector2D start = { topLeftPos.x - mStride, topLeftPos.y + i * mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				newGridVertexDeque.push_back(startVertex);
			}

			mGridVertexList2D.push_front(newGridVertexDeque);

			xFlag = true;
		}

		topLeftPos = mGridVertexList2D.front().front()->GetXY();
		if (topLeftPos.y - mStride >= minY)
		{
			int i = 0;
			for (auto& gridVertexDeque : mGridVertexList2D)
			{
				scVector2D start = { topLeftPos.x + i * mStride, topLeftPos.y - mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				gridVertexDeque.push_front(startVertex);
				i++;
			}

			yFlag = true;
		}


	} while (xFlag || yFlag);



	// ######### bottomRight ##########
	topLeftPos = mGridVertexList2D.front().front()->GetXY();
	scVector2D bottomRightPos;

	do
	{
		xFlag = false;
		yFlag = false;

		bottomRightPos = mGridVertexList2D.back().back()->GetXY();

		// Remove
		if (bottomRightPos.y > maxY)
		{
			for (auto& gridVertexDeque : mGridVertexList2D)
			{
				gridVertexDeque.pop_back();
			}

			yFlag = true;
		}

		if (bottomRightPos.x > maxX)
		{
			mGridVertexList2D.pop_back();

			xFlag = true;
		}
	} while (xFlag || yFlag);


	do
	{
		xFlag = false;
		yFlag = false;

		// Add
		bottomRightPos = mGridVertexList2D.back().back()->GetXY();
		if (bottomRightPos.x + mStride <= maxX)
		{
			std::list<std::shared_ptr<scVertexQtVisual>> newGridVertexDeque;

			for (int i = 0; i < mGridVertexList2D.front().size(); i++)
			{
				scVector2D start = { bottomRightPos.x + mStride, topLeftPos.y + i * mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				newGridVertexDeque.push_back(startVertex);
			}

			mGridVertexList2D.push_back(newGridVertexDeque);

			xFlag = true;
		}

		bottomRightPos = mGridVertexList2D.back().back()->GetXY();
		if (bottomRightPos.y + mStride <= maxY)
		{
			int i = 0;
			for (auto& gridVertexDeque : mGridVertexList2D)
			{
				scVector2D start = { topLeftPos.x + i * mStride, bottomRightPos.y + mStride };
				shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
				gridVertexDeque.push_back(startVertex);
				i++;
			}

			yFlag = true;
		}
	} while (xFlag || yFlag);

}
