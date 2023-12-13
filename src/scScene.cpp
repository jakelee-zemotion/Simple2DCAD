#include "scScene.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"

using namespace std;

scScene::scScene(const QRect& viewportSize)
	:mViewportSize(viewportSize)
{
	mVertexCreatedCount = 0;
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

	for (const auto& shape : mFaceList)
	{
		shape->Paint(painter);
	}
}

void scScene::AddStartVertex(const QPointF& point)
{
	shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(point, mViewportSize);
	mVertexList.push_back(startVertex);

	mDrawStartVertex = startVertex;
}

shared_ptr<scShapeQtVisual> scScene::AddEndVertex(const QPointF& point)
{
	// Copy the vertices.
	shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
	shared_ptr<scVertexQtVisual> endVertex = make_shared<scVertexQtVisual>(point, mViewportSize);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mViewportSize);

	// Add Vertices.
	mVertexList.push_back(endVertex);

	// Add a new line.
	mLineList.push_back(newLine);

	// Count the number of vertices created.
	mVertexCreatedCount++;
	return endVertex;
}

void scScene::EndDrawing()
{
	if (mVertexList.empty() || mLineList.empty())
		return;

	// Remove the drawing line.
	mVertexList.pop_back();
	mLineList.pop_back();

	// Remove the single vertex.
	if (mVertexCreatedCount < 2 && !mVertexList.empty())
		mVertexList.pop_back();

	mVertexCreatedCount = 0;

	//list<scLineQtVisual> 

}

shared_ptr<scShapeQtVisual> scScene::HitTest(const QPointF& currMousePos, SELECT shapeType)
{
	list<shared_ptr<scShapeQtVisual>>* shapeList;

	switch (shapeType)
	{
		case SELECT::VERTEX : 
			shapeList = &mVertexList;  break;

		case SELECT::LINE : 
			shapeList = &mLineList; break;

		case SELECT::FACE :
		default:
			shapeList = &mLineList;
			break;
	}

	// Hit testing
	for (auto iter = shapeList->rbegin(); iter != shapeList->rend(); iter++)
	{
		shared_ptr<scShapeQtVisual>& point = *iter;

		if (point->HitTest(currMousePos))
		{
			return point;
		}
	}

	return nullptr;
}

bool scScene::CanCreateFace(const QPointF& currMousePos)
{
	return 
		mVertexCreatedCount >= 3 
		&& mDrawStartVertex != nullptr 
		&& mDrawStartVertex->HitTest(currMousePos);
}
