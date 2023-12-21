#include "scScene.h"

#include "scCoordinateHelper.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scFaceQtVisual.h"

using namespace std;

scScene::scScene(const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:mCoordinateHelper(coordinateHelper)
{
	mVertexCreatedCount = 0;
}

scScene::~scScene()
{
}

void scScene::Render(QPainter& painter)
{
	// Vertices, lines, and faces are pushed to mDrawShapeList in the order they are drawn. 
	// So, we can draw shapes in a specific order by iterating the mDrawShapeList.
	auto iter = mDrawShapeList.begin();
	while (iter != mDrawShapeList.end())
	{
		auto& shapePtr = *iter;

		// Erase the removed shape.
		// mDrawShapeList has elements of mVertexList, mLineList, and mFaceList as weak_ptr.
		// So, if the shared_ptr pointed to by Weak_ptr has been popped from the list, 
		// we need to erase the Shape from mDrawShapeList.
		if (shapePtr.expired())
		{
			iter = mDrawShapeList.erase(iter);
			continue;
		}

		shapePtr.lock()->Paint(painter);
		iter++;
	}
}

// L1[V1, V2], L2[V2, V3], L3[V3, V1], F1[L1, L2, L3]
// 
// The drawing order for the example above is:
// V1 V2 L1 V3 L2 L3 F1
// 
// The insertion order we want is:
// F1 L1 L2 L3 V1 V2 V3 
// 
// So, Insertion iterators are:
// [previous elements] [F1] [L1 L2 L3] [V1 V2 V3] 
// --------------------------ก่---------ก่-------ก่
// -------------------------Face-------Line----Vertex
// 
// Note that insert() in std::list inserts an element before the iterator.
// Also, VertexIterator is not needed because we can use push_back().

shared_ptr<scVertexQtVisual> scScene::AddStartVertex(const QPointF& point)
{
	shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(point, mCoordinateHelper);
	mVertexList.push_back(startVertex);

	mDrawShapeList.push_back(startVertex);

	// Initialize mInsertLineIter.
	mInsertLineIter = mDrawShapeList.end();
	mInsertLineIter--;

	return startVertex;
}

shared_ptr<scVertexQtVisual> scScene::AddEndVertex(const QPointF& point)
{
	// Copy the vertices.
	shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
	shared_ptr<scVertexQtVisual> endVertex = make_shared<scVertexQtVisual>(point, mCoordinateHelper);

	// Ref the vertices.
	shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);

	// Add Vertices.
	mVertexList.push_back(endVertex);
	mDrawShapeList.push_back(endVertex);

	// Add a new line.
	mLineList.push_back(newLine);
	mDrawShapeList.insert(mInsertLineIter, newLine);

	// Initialize mInsertFaceIter.
	if (mVertexCreatedCount == 0)
	{
		mInsertFaceIter = mInsertLineIter;
		mInsertFaceIter--;
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

		shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
		mLineList.push_back(newLine);
		mDrawShapeList.insert(mInsertLineIter, newLine);


		// Copy LineData.
		list<shared_ptr<scLineData>> faceLineList;
		for (; lineIter != mLineList.end(); lineIter++)
		{
			shared_ptr<scLineData> line = dynamic_pointer_cast<scLineQtVisual>(*lineIter)->GetLineData();
			faceLineList.push_back(line);
		}

		// Add a new face.
		shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(faceLineList, mCoordinateHelper);
		mFaceList.push_back(newFace);
		mDrawShapeList.insert(mInsertFaceIter, newFace);
	}

	// Reset
	mVertexCreatedCount = 0;

	qDebug() << mFaceList.size();
}

std::shared_ptr<scShapeQtVisual> scScene::HitTest(const QPointF& currMousePos, SHAPE_TYPE shapeType, scShapeID noTestShapeID)
{
	// Hit testing
	// The order is vertex, line, and face.
	vector<list<shared_ptr<scShapeQtVisual>>*> shapeLists = { &mVertexList, &mLineList, &mFaceList };

	for (int i = 0; i < 3; i++)
	{
		// Check shapeType using bitwise operators.
		// 001 is Vertex, 010 is Line, 100 is Face and 111 is ALL.
		if (!((shapeType >> i) & 1))
			continue;

		// Reverse search
		for (auto iter = shapeLists[i]->rbegin(); iter != shapeLists[i]->rend(); iter++)
		{
			shared_ptr<scShapeQtVisual>& shape = *iter;

			if (shape->HitTest(currMousePos)
				&& shape->GetID() != noTestShapeID) // The specific shape is excluded from the search.
			{
				return shape;
			}
		}

	}

	return nullptr;
}

void scScene::AddBoundingBoxOfFace(const shared_ptr<scFaceQtVisual>& face)
{
	assert(face->GetShapeType() == SHAPE_TYPE::FACE);

	scBoundingBox boundingBox = face->GetBoundingBox();

}

int scScene::GetVertexCreatedCount() const
{
	return mVertexCreatedCount;
}
