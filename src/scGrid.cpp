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
	mSizeX = mViewportSize.width() / mStride;
	mSizeY = mViewportSize.height() / mStride;
	mGridVertexVector = vector<vector<shared_ptr<scVertexQtVisual>>>(mSizeX, vector<shared_ptr<scVertexQtVisual>>(mSizeY));


	for (int i = 0; i < mSizeX; i++)
	{
		for (int j = 0; j < mSizeY; j++)
		{
			double x = i * mStride;
			double y = j * mStride;

			scVector2D start = { x,  y };

			shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(start, mCoordinateHelper);
			mGridVertexVector[i][j] = startVertex;
		}
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	for (int i = 0; i < mSizeX; i ++)
	{
		for (int j = 0; j < mSizeY; j ++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexVector[i][j];

			vertex->Paint(painter);
		}
	}
}

std::shared_ptr<scShapeQtVisual> scGrid::HitTest(const scVector2D& currMousePos)
{
	for (int i = 0; i < mSizeX; i++)
	{
		for (int j = 0; j < mSizeY; j++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexVector[i][j];

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

	for (int i = 0; i < mSizeX; i++)
	{
		for (int j = 0; j < mSizeY; j++)
		{
			shared_ptr<scVertexQtVisual> vertex = mGridVertexVector[i][j];
			scVector2D pos = vertex->GetXY();

			double width = static_cast<double>(mViewportSize.width());
			double height = static_cast<double>(mViewportSize.height());

			if (pos.x < 0.0)
			{
				pos.x += width;
			}
			else if (pos.x > width)
			{
				pos.x -= width;
			}

			if (pos.y < 0.0)
			{
				pos.y += height;
			}
			else if (pos.y > height)
			{
				pos.y -= height;
			}

			vertex->SetXY(pos);
		}
	}
}

void scGrid::ZoomEvent(int mouseDir)
{
	int count = mCamera.GetZoomOutCount();


	if (count % 5 == 0)
	{
		for (int i = 0; i < mSizeX; i++)
		{
			for (int j = 0; j < mSizeY; j++)
			{
				double x = i * mStride;
				double y = j * mStride;

				shared_ptr<scVertexQtVisual> vertex = mGridVertexVector[i][j];
				scVector2D pos = { x, y };


				vertex->SetXY(pos);
			}
		}
	}
}
