#include "scScene.h"

using namespace std;

scScene::scScene(const QRect& viewportSize)
	:mViewportSize(viewportSize)
{

}

scScene::~scScene()
{
}

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

shared_ptr<scShapeQtVisual> scScene::AddVertex(const QPointF& point, bool isDrawing)
{
	shared_ptr<scVertexQtVisual> startVertex;

	if (!isDrawing)
	{
		// Put two points to create a line on the first click.
		// Therefore, the second point is adjusted in MouseMoveEvent.
		startVertex 
			= std::make_shared<scVertexQtVisual>(point, mViewportSize);
		mVertexList.push_back(startVertex);
	}
	else
	{
		startVertex = mVertexList.back();
	}

	// Copy the vertices.
	shared_ptr<scVertexQtVisual> endVertex = std::make_shared<scVertexQtVisual>(point, mViewportSize);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = std::make_shared<scLineQtVisual>(startVertex, endVertex, mViewportSize);

	// Add Vertices.
	mVertexList.push_back(endVertex);

	// Add a new line and ployline.
	mLineList.push_back(newLine);


	return endVertex;
}

void scScene::EndDrawing()
{
	if (mVertexList.empty() || mLineList.empty())
		return;

	mVertexList.pop_back();
	mLineList.pop_back();
}

shared_ptr<scShapeQtVisual> scScene::GetSelectedVertex(const QPointF& currMousePos, int shapeType)
{
	list<shared_ptr<scShapeQtVisual>>* shapeList;

	switch (shapeType)
	{
		//case 0: shapeList = &mVertexList;  break;
	}

	for (const auto& point : mVertexList)
	{
		if (point->HitTest(currMousePos))
		{
			return point;
		}
	}

	return nullptr;
}

shared_ptr<scShapeQtVisual> scScene::GetSelectedLine(const QPointF& currMousePos)
{
	for (const auto& line : mLineList)
	{
		if (line->HitTest(currMousePos))
		{
			return line;
		}
	}

	return nullptr;
}
