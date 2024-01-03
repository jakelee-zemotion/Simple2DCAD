#include "scGrid.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scCoordinateHelper.h"
#include "scMatrixVectorHelper.h"
#include "scCamera.h"

#include <QPainter>

using namespace std;

scGrid::scGrid(
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper, 
	const scCamera& camera, 
	const QRect& viewportSize)
		:mCoordinateHelper(coordinateHelper), mCamera(camera), mViewportSize(viewportSize)
{
	double orgrinX = mViewportSize.width() / 2.0;
	double orgrinY = mViewportSize.height() / 2.0;

	double offset = 1000.0;

	for (double i = -offset; i < offset; i += 50.0)
	{
		scVector2D start = { orgrinX + i, -offset };
		scVector2D end = { orgrinX + i, offset };

		shared_ptr<scVertexQtVisual> startVertex = make_shared< scVertexQtVisual>(start, mCoordinateHelper);
		shared_ptr<scVertexQtVisual> endVertex = make_shared< scVertexQtVisual>(end, mCoordinateHelper);

		shared_ptr<scLineQtVisual> line = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
		mLineList.push_back(line);


		start = { -offset, orgrinY + i };
		end = { offset, orgrinY + i };

		startVertex = make_shared< scVertexQtVisual>(start, mCoordinateHelper);
		endVertex = make_shared< scVertexQtVisual>(end, mCoordinateHelper);

		line = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
		mLineList.push_back(line);


		
	}
}

scGrid::~scGrid()
{
}

void scGrid::Paint(QPainter& painter)
{
	for (const auto& line : mLineList)
	{
		line->Paint(painter);
	}
}
