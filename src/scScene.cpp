#include "scScene.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scFaceQtVisual.h"

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
	for (const auto& shape : mFaceList)
	{
		shape->Paint(painter);
	}

	for (const auto& shape : mLineList)
	{
		shape->Paint(painter);
	}

	for (const auto& shape : mVertexList)
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

void scScene::EndDrawing(bool canCreateFace)
{
	if (mVertexList.empty() || mLineList.empty())
		return;

	// Remove the drawing line.
	mVertexList.pop_back();
	mLineList.pop_back();

	// Remove the single vertex.
	if (mVertexCreatedCount < 2 && !mVertexList.empty())
		mVertexList.pop_back();


	if (canCreateFace)
	{
		// Find the starting vertex of the face.
		auto listIter = mLineList.end();
		auto vertexIter = mVertexList.end();
		for (int i = 0; i < mVertexCreatedCount - 1; i++)
		{
			listIter--;
			vertexIter--;
		}
		vertexIter--;

		if (mVertexList.empty())
			return;

		// Add the last line of the face.
		shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
		shared_ptr<scVertexQtVisual> endVertex = dynamic_pointer_cast<scVertexQtVisual>(*vertexIter);

		shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mViewportSize);
		mLineList.push_back(newLine);


		// Copy LineData.
		list<shared_ptr<scLineData>> faceLineList;
		for (; listIter != mLineList.end(); listIter++)
		{
			shared_ptr<scLineData> line = dynamic_pointer_cast<scLineQtVisual>(*listIter)->GetLineData();
			faceLineList.push_back(line);
		}

		// Add a new face.
		shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(faceLineList, mViewportSize);
		mFaceList.push_back(newFace);
	}

	// Reset
	mVertexCreatedCount = 0;

	qDebug() << mFaceList.size();
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
		shared_ptr<scShapeQtVisual>& shape = *iter;

		if (shape->HitTest(currMousePos))
		{
			return shape;
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
