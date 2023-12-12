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
			= make_shared<scVertexQtVisual>(point, mViewportSize);
		mVertexList.push_back(startVertex);
	}
	else
	{
		// mVertexList element is scShapeQtVisual and must be downcast.
		startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
	}

	// Copy the vertices.
	shared_ptr<scVertexQtVisual> endVertex = make_shared<scVertexQtVisual>(point, mViewportSize);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mViewportSize);

	// Add Vertices.
	mVertexList.push_back(endVertex);

	// Add a new line.
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

shared_ptr<scShapeQtVisual> scScene::HitTest(const QPointF& currMousePos, int shapeType)
{
	list<shared_ptr<scShapeQtVisual>>* shapeList;

	switch (shapeType)
	{
		case 0: shapeList = &mVertexList;  break;
		case 1: shapeList = &mLineList; break;
	}

	for (const auto& point : *shapeList)
	{
		if (point->HitTest(currMousePos))
		{
			return point;
		}
	}

	return nullptr;
}
