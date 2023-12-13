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

	auto iter = mLineList.end();
	for (int i = 0; i < mVertexCreatedCount -1; i++)
		iter--;

	list<shared_ptr<scLineData>> faceLineList;
	for (; iter != mLineList.end(); iter++)
	{
		shared_ptr<scLineData> line = dynamic_pointer_cast<scLineQtVisual>(*iter)->GetLineData();
		faceLineList.push_back(line);
	}


	//shared_ptr<scVertexData> v1 = make_shared<scVertexData>();
	//v1->SetX(100.0); v1->SetY(100.0);

	//shared_ptr<scVertexData> v2 = make_shared<scVertexData>();
	//v2->SetX(100.0); v2->SetY(200.0);

	//shared_ptr<scVertexData> v3 = make_shared<scVertexData>();
	//v3->SetX(200.0); v3->SetY(200.0);

	//shared_ptr<scVertexData> v4 = make_shared<scVertexData>();
	//v4->SetX(200.0); v4->SetY(100.0);

	//shared_ptr<scLineData> line1 = make_shared<scLineData>();
	//line1->SetStartVertex(v1); line1->SetEndVertex(v2);

	//shared_ptr<scLineData> line2 = make_shared<scLineData>();
	//line2->SetStartVertex(v2); line2->SetEndVertex(v3);

	//shared_ptr<scLineData> line3 = make_shared<scLineData>();
	//line3->SetStartVertex(v3); line3->SetEndVertex(v4);

	//shared_ptr<scLineData> line4 = make_shared<scLineData>();
	//line4->SetStartVertex(v4); line4->SetEndVertex(v1);

	//faceLineList.push_back(line1);
	//faceLineList.push_back(line2);
	//faceLineList.push_back(line3);
	//faceLineList.push_back(line4);


	shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(faceLineList, mViewportSize);
	mFaceList.push_back(newFace);


	mVertexCreatedCount = 0;

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
