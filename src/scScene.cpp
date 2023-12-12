#include "scScene.h"

using namespace std;

void scScene::Render(QPainter& painter)
{
	for (const auto& shape : mLineList)
	{
		shape->Paint(painter);
	}

	for (const auto& shape : mVertexList)
	{
		shape->Paint(painter);
	}
}

void scScene::AddVertex(QPointF& point, bool isDrawing)
{
	shared_ptr<scVertexQtVisual> startVertex;

	if (!isDrawing)
	{
		// Put two points to create a line on the first click.
		// Therefore, the second point is adjusted in MouseMoveEvent.
		startVertex = std::make_shared<scVertexQtVisual>(point);
		mVertexList.push_back(startVertex);
	}
	else
	{
		startVertex = mVertexList.back();
	}

	// Copy the vertices.
	shared_ptr<scVertexQtVisual> endVertex = std::make_shared<scVertexQtVisual>(point);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = std::make_shared<scLineQtVisual>(startVertex, endVertex);

	// Add Vertices.
	mVertexList.push_back(endVertex);

	// Add a new line and ployline.
	mLineList.push_back(newLine);
}

void scScene::EndDrawing()
{
	if (mVertexList.empty() || mLineList.empty())
		return;

	mVertexList.pop_back();
	mLineList.pop_back();

}

void scScene::MoveDrawingPoint(QPointF& point)
{
	if (mVertexList.empty())
		return;

	shared_ptr<scVertexQtVisual> lastVertex = mVertexList.back();

	lastVertex->SetXY(point.x(), point.y());
}