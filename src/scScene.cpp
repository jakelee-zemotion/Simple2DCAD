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
	auto iter = mShapeList.begin();
	while (iter != mShapeList.end())
	{
		auto& shapePtr = *iter;

		// Erase the removed shape.
		if (shapePtr.expired())
		{
			iter = mShapeList.erase(iter);
			continue;
		}

		shapePtr.lock()->Paint(painter);
		iter++;
	}
}

shared_ptr<scShapeQtVisual> scScene::AddStartVertex(const QPointF& point)
{
	shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(point, mViewportSize);
	mVertexList.push_back(startVertex);
	mShapeList.push_back(startVertex);

	return startVertex;
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
	mShapeList.push_back(endVertex);

	// Add a new line.
	mLineList.push_back(newLine);
	mShapeList.push_back(newLine);

	// Count the number of vertices created.
	mVertexCreatedCount++;
	return endVertex;
}

void scScene::EndDrawing(bool canCreateFace)
{
	assert(!mVertexList.empty() && !mLineList.empty());

	// Remove the drawing line.
	mVertexList.pop_back();
	mLineList.pop_back();

	// Remove the single vertex.
	if (mVertexCreatedCount < 2)
	{
		assert(!mVertexList.empty());
		mVertexList.pop_back();
	}


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
		vertexIter--; // vertexCount = lineCount + 1

		assert(!mVertexList.empty());

		// Add the last line of the face.
		shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
		shared_ptr<scVertexQtVisual> endVertex = dynamic_pointer_cast<scVertexQtVisual>(*vertexIter);

		shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mViewportSize);
		mLineList.push_back(newLine);
		mShapeList.push_back(newLine);


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
		mShapeList.push_back(newFace);
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
			shapeList = &mFaceList;
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

int scScene::GetVertexCreatedCount() const
{
	return mVertexCreatedCount;
}
