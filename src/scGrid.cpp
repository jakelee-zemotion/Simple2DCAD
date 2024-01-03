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
	double orgrinX = mViewportSize.width() / 2.0;
	double orgrinY = mViewportSize.height() / 2.0;

	mGridVertexVector = vector<vector<shared_ptr<scVertexQtVisual>>>(mSize, vector<shared_ptr<scVertexQtVisual>>(mSize));


	for (int i = 0; i < mSize; i++)
	{
		for (int j = 0; j < mSize; j++)
		{
			double x = -mOffset + i * mStride;
			double y = -mOffset + j * mStride;

			scVector2D start = { orgrinX + x,  orgrinY + y };
			//scVector2D end = { orgrinX + i, offset };

			shared_ptr<scVertexQtVisual> startVertex = make_shared< scVertexQtVisual>(start, mCoordinateHelper);
			//shared_ptr<scVertexQtVisual> endVertex = make_shared< scVertexQtVisual>(end, mCoordinateHelper);

			//shared_ptr<scLineQtVisual> line = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
			//mLineList.push_back(line);
			mGridVertexVector[i][j] = startVertex;


			/*start = { -offset, orgrinY + i };
			end = { offset, orgrinY + i };

			startVertex = make_shared< scVertexQtVisual>(start, mCoordinateHelper);
			endVertex = make_shared< scVertexQtVisual>(end, mCoordinateHelper);

			line = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
			mLineList.push_back(line);
	*/
		}
		
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	int cameraStride = (mCamera.GetZoomOutCount() / mDegree) + 1;

	qDebug() << cameraStride;

	for (int i = 0; i < mSize; i += cameraStride)
	{
		for (int j = 0; j < mSize; j += cameraStride)
		{
			mGridVertexVector[i][j]->Paint(painter);
		}
	}
}
