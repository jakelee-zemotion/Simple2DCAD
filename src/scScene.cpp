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
	shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(SHAPE_TYPE::VERTEX, point, mViewportSize);
	mVertexList.push_back(startVertex);

	mShapeList.push_back(startVertex);
	mLineIter = mShapeList.end();
	mLineIter--;

	return startVertex;
}

shared_ptr<scShapeQtVisual> scScene::AddEndVertex(const QPointF& point)
{
	// Copy the vertices.
	shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
	shared_ptr<scVertexQtVisual> endVertex = make_shared<scVertexQtVisual>(SHAPE_TYPE::VERTEX, point, mViewportSize);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(SHAPE_TYPE::LINE, startVertex, endVertex, mViewportSize);

	// Add Vertices.
	mVertexList.push_back(endVertex);
	mShapeList.push_back(endVertex);

	// Add a new line.
	mLineList.push_back(newLine);
	mShapeList.insert(mLineIter, newLine);

	if (mVertexCreatedCount == 0)
	{
		mFaceIter = mLineIter;
		mFaceIter--;
	}

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
		auto lineIter = mLineList.end();
		auto vertexIter = mVertexList.end();
		for (int i = 0; i < mVertexCreatedCount - 1; i++)
		{
			lineIter--;
			vertexIter--;
		}
		vertexIter--; // vertexCount = lineCount + 1

		assert(!mVertexList.empty());

		// Add the last line of the face.
		shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
		shared_ptr<scVertexQtVisual> endVertex = dynamic_pointer_cast<scVertexQtVisual>(*vertexIter);

		shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(SHAPE_TYPE::LINE, startVertex, endVertex, mViewportSize);
		mLineList.push_back(newLine);
		mShapeList.insert(mLineIter, newLine);


		// Copy LineData.
		list<shared_ptr<scLineData>> faceLineList;
		for (; lineIter != mLineList.end(); lineIter++)
		{
			shared_ptr<scLineData> line = dynamic_pointer_cast<scLineQtVisual>(*lineIter)->GetLineData();
			faceLineList.push_back(line);
		}

		// Add a new face.
		shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(SHAPE_TYPE::FACE, faceLineList, mViewportSize);
		mFaceList.push_back(newFace);
		mShapeList.insert(mFaceIter, newFace);
	}

	// Reset
	mVertexCreatedCount = 0;

	qDebug() << mFaceList.size();
}

shared_ptr<scShapeQtVisual> scScene::HitTest(const QPointF& currMousePos, SHAPE_TYPE shapeType)
{
	list<shared_ptr<scShapeQtVisual>>* shapeList;

	switch (shapeType)
	{
		case SHAPE_TYPE::VERTEX :
			shapeList = &mVertexList;  break;

		case SHAPE_TYPE::LINE :
			shapeList = &mLineList; break;

		case SHAPE_TYPE::FACE :
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
