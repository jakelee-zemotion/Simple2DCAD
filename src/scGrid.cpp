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

	mGridVertexDeque = deque<deque<shared_ptr<scVertexQtVisual>>>(sizeX, deque<shared_ptr<scVertexQtVisual>>(sizeY));

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			double x = i * mStride;
			double y = j * mStride;

			scVector2D start = { x,  y };

			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
			mGridVertexDeque[i][j] = startVertex;
		}
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	int sizeX = mGridVertexDeque.size();
	int sizeY = mGridVertexDeque[0].size();

	for (int i = 0; i < sizeX; i ++)
	{
		for (int j = 0; j < sizeY; j ++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque[i][j];

			vertex->Paint(painter);
		}
	}
}

std::shared_ptr<scShapeQtVisual> scGrid::HitTest(const scVector2D& currMousePos)
{
	int sizeX = mGridVertexDeque.size();
	int sizeY = mGridVertexDeque[0].size();

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque[i][j];

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
	int sizeX = mGridVertexDeque.size();
	int sizeY = mGridVertexDeque[0].size();

	double minX = 0.0;
	double minY = 0.0;
	double maxX = static_cast<double>(mViewportSize.width());
	double maxY = static_cast<double>(mViewportSize.height());

	scVector2D topLeftPos = mGridVertexDeque.front().front()->GetXY();

	if (topLeftPos.y < minY)
	{
		for (int i = 0; i < sizeX; i++)
		{
			mGridVertexDeque[i].push_back(mGridVertexDeque[i].front());
			mGridVertexDeque[i].pop_front();
		}
	}

	if (topLeftPos.x < minX)
	{
		mGridVertexDeque.push_back(mGridVertexDeque.front());
		mGridVertexDeque.pop_front();
	}

	scVector2D bottomRightPos = mGridVertexDeque.back().back()->GetXY();
	if (bottomRightPos.y > maxY)
	{
		for (int i = 0; i < sizeX; i++)
		{
			mGridVertexDeque[i].push_front(mGridVertexDeque[i].back()); 
			mGridVertexDeque[i].pop_back();
		}
	}

	if (bottomRightPos.x > maxX)
	{
		mGridVertexDeque.push_front(mGridVertexDeque.back());
		mGridVertexDeque.pop_back();
	}



	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque[i][j];
			scVector2D pos = vertex->GetXY();

			double minX = 0.0;
			double minY = 0.0;
			double maxX = static_cast<double>(mViewportSize.width());
			double maxY = static_cast<double>(mViewportSize.height());

			if (pos.x < minX)
			{
				pos.x += maxX;
			}
			else if (pos.x > maxX)
			{
				pos.x -= maxX;
			}

			if (pos.y < minY)
			{
				pos.y += maxY;
			}
			else if (pos.y > maxY)
			{
				pos.y -= maxY;
			}

			vertex->SetXY(pos);
		}
	}
}

void scGrid::ZoomEvent(int mouseDir)
{
	int count = mCamera.GetZoomOutCount();

	if (mouseDir > 0) // Zoom In
	{
		int sizeX = mGridVertexDeque.size();
		int sizeY = mGridVertexDeque[0].size();

		double minX = 0.0;
		double minY = 0.0;
		double maxX = static_cast<double>(mViewportSize.width());
		double maxY = static_cast<double>(mViewportSize.height());

		scVector2D topLeftPos = mGridVertexDeque.front().front()->GetXY();

		if (topLeftPos.y < minY)
		{
			for (int i = 0; i < sizeX; i++)
			{
				mGridVertexDeque[i].pop_front();
			}
		}

		if (topLeftPos.x < minX)
		{
			mGridVertexDeque.pop_front();
		}

		sizeX = mGridVertexDeque.size();
		sizeY = mGridVertexDeque[0].size();
		scVector2D bottomRightPos = mGridVertexDeque.back().back()->GetXY();
		if (bottomRightPos.y > maxY)
		{
			for (int i = 0; i < sizeX; i++)
			{
				mGridVertexDeque[i].pop_back();
			}
		}

		if (bottomRightPos.x > maxX)
		{
			mGridVertexDeque.pop_back();
		}
	}
	else
	{
		int sizeX = mGridVertexDeque.size();
		int sizeY = mGridVertexDeque[0].size();

		double minX = 0.0;
		double minY = 0.0;
		double maxX = static_cast<double>(mViewportSize.width());
		double maxY = static_cast<double>(mViewportSize.height());

		scVector2D topLeftPos = mGridVertexDeque.front().front()->GetXY();

		if (topLeftPos.y < minY)
		{
			for (int i = 0; i < sizeX; i++)
			{
				mGridVertexDeque[i].pop_front();
			}
		}

	}


	/*if (count % 5 == 0)
	{
		for (int i = 0; i < mSizeX; i++)
		{
			for (int j = 0; j < mSizeY; j++)
			{
				double x = i * mStride;
				double y = j * mStride;

				shared_ptr<scVertexQtVisual> vertex = mGridVertexDeque[i][j];
				scVector2D pos = { x, y };


				vertex->SetXY(pos);
			}
		}
	}*/
}
