#include "scScene.h"

// system
#include <map>

// qt
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>

// Simple2DCAD
#include "scGrid.h"
#include "scCoordinateHelper.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scFaceQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scRotateControlVertexQtVisual.h"

using namespace std;

scScene::scScene(const std::shared_ptr<scCoordinateHelper>& coordinateHelper, const std::shared_ptr<scGrid>& grid)
	:mCoordinateHelper(coordinateHelper), mGrid(grid)
{
	mVertexCreatedCount = 0;
}

scScene::~scScene()
{
}

void scScene::Render(QPainter& painter)
{
	mGrid->Paint(painter);

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
// --------------------------↑---------↑-------↑
// -------------------------Face-------Line----Vertex
// 
// Note that insert() in std::list inserts an element before the iterator.
// Also, VertexIterator is not needed because we can use push_back().

shared_ptr<scVertexQtVisual> scScene::AddStartVertex(const scVector2D& pos)
{
	const shared_ptr<scVertexQtVisual> startVertex = make_shared<scVertexQtVisual>(pos, mCoordinateHelper);
	mVertexList.push_back(startVertex);

	mDrawShapeList.push_back(startVertex);

	// Initialize mInsertLineIter.
	mInsertLineIter = mDrawShapeList.end();
	mInsertLineIter--;

	return startVertex;
}

shared_ptr<scVertexQtVisual> scScene::AddEndVertex(const scVector2D& pos)
{
	// Copy the vertices.
	const shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
	const shared_ptr<scVertexQtVisual> endVertex = make_shared<scVertexQtVisual>(pos, mCoordinateHelper);

	// Ref the vertices.
	const shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);

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
		const shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(mVertexList.back());
		const shared_ptr<scVertexQtVisual> endVertex = dynamic_pointer_cast<scVertexQtVisual>(*vertexIter);

		const shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
		mLineList.push_back(newLine);
		mDrawShapeList.insert(mInsertLineIter, newLine);

		// Copy LineData.
		list<shared_ptr<scLineQtVisual>> faceLineList;
		for (; lineIter != mLineList.end(); lineIter++)
		{
			shared_ptr<scLineQtVisual> line = dynamic_pointer_cast<scLineQtVisual>(*lineIter);
			faceLineList.push_back(line);
		}

		// Add a new face.
		const shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(faceLineList, mCoordinateHelper);
		mFaceList.push_back(newFace);
		mDrawShapeList.insert(mInsertFaceIter, newFace);
	}

	// Reset
	mVertexCreatedCount = 0;
}

std::shared_ptr<scShapeQtVisual> scScene::HitTest(const scVector2D& currMousePos, const scShapeType& shapeType, const scShapeID& noTestShapeID)
{
	// Hit testing
	// The order is vertex, line, and face.
	const vector<list<shared_ptr<scShapeQtVisual>>*> shapeLists = { &mVertexList, &mLineList, &mFaceList };

	for (int i = 0; i < 3; i++)
	{
		// Check shapeType using bitwise operators.
		// 001 is Vertex, 010 is Line, 100 is Face and 111 is ALL.
		if (!((shapeType >> i) & 1))
			continue;

		// Reverse search
		for (auto iter = shapeLists[i]->rbegin(); iter != shapeLists[i]->rend(); iter++)
		{
			const shared_ptr<scShapeQtVisual>& shape = *iter;

			if (shape->HitTest(currMousePos)
				&& shape->GetID() != noTestShapeID) // The specific shape is excluded from the search.
			{
				return shape;
			}
		}
	}

	// Grid HitTesting is performed at the end.
	return mGrid->HitTest(currMousePos);
}

void scScene::SaveData(const string& fileName)
{
	QJsonObject data;
	QJsonObject vertices;

	for (const auto& ver : mVertexList)
	{
		const shared_ptr<scVertexQtVisual> vertex = dynamic_pointer_cast<scVertexQtVisual>(ver);
		
		QJsonObject vData;
		const scVector2D pos = vertex->GetXY();

		vData["x"] = pos.x;
		vData["y"] = pos.y;

		const QString id = QString::fromStdString(vertex->GetID());
		vertices[id] = vData;
	}

	QJsonObject lines;

	for (const auto& li : mLineList)
	{
		const shared_ptr<scLineQtVisual> line = dynamic_pointer_cast<scLineQtVisual>(li);

		QJsonObject lData;
		scShapeID sid = line->GetStartVertexID();
		scShapeID eid = line->GetEndVertexID();

		lData["start"] = QString::fromStdString(sid);
		lData["end"] = QString::fromStdString(eid);

		const QString id = QString::fromStdString(line->GetID());
		lines[id] = lData;
	}

	QJsonObject faces;

	for (const auto& fa : mFaceList)
	{
		const shared_ptr<scFaceQtVisual> face = dynamic_pointer_cast<scFaceQtVisual>(fa);

		QJsonObject fData;
		list<scShapeID> ids = face->GetLineStartIDs();

		QJsonArray idsArray;
		for (auto& id : ids)
		{
			idsArray.push_back(QString::fromStdString(id));
		}

		fData["lines"] = idsArray;

		const QString id = QString::fromStdString(face->GetID());
		faces[id] = fData;
	}

	QJsonArray orderArray;

	for (const auto& sh : mDrawShapeList)
	{
		if (!sh.expired())
		{
			const QString idQStr = QString::fromStdString(sh.lock()->GetID());
			orderArray.push_back(idQStr);
		}
	}

	data["vertices"] = vertices;
	data["lines"] = lines;
	data["faces"] = faces;
	data["orders"] = orderArray;

	QFile saveFile(QString::fromStdString(fileName));
	saveFile.open(QIODevice::WriteOnly);

	const QJsonDocument saveDoc(data);
	saveFile.write(saveDoc.toJson());
	saveFile.close();
}

void scScene::LoadData(const string& fileName)
{
	ClearData();

	QFile loadFile(QString::fromStdString(fileName));
	loadFile.open(QIODevice::ReadOnly);

	const QByteArray loadData = loadFile.readAll();
	const QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
	const QJsonObject data = loadDoc.object();

	const QJsonObject vertices = data["vertices"].toObject();
	const QJsonObject lines = data["lines"].toObject();
	const QJsonObject faces = data["faces"].toObject();
	const QJsonArray orders = data["orders"].toArray();

	map<string, shared_ptr<scShapeQtVisual>> ShapeMap;

	for (const auto& key : vertices.keys())
	{
		const QJsonObject vertex = vertices[key].toObject();

		const double x = vertex["x"].toDouble();
		const double y = vertex["y"].toDouble();
		const scVector2D pos = { x, y };

		const shared_ptr<scVertexQtVisual> newVertex = make_shared<scVertexQtVisual>(pos, mCoordinateHelper);
		const string id = key.toStdString();

		ShapeMap[id] = newVertex;
		mVertexList.push_back(newVertex);
	}

	for (const auto& key : lines.keys())
	{
		const QJsonObject line = lines[key].toObject();

		const string startID = line["start"].toString().toStdString();
		const string endID = line["end"].toString().toStdString();

		const shared_ptr<scVertexQtVisual> startVertex = dynamic_pointer_cast<scVertexQtVisual>(ShapeMap[startID]);
		const shared_ptr<scVertexQtVisual> endVertex = dynamic_pointer_cast<scVertexQtVisual>(ShapeMap[endID]);

		const shared_ptr<scLineQtVisual> newLine = make_shared<scLineQtVisual>(startVertex, endVertex, mCoordinateHelper);
		const string id = key.toStdString();

		ShapeMap[id] = newLine;
		mLineList.push_back(newLine);
	}

	for (const auto& key : faces.keys())
	{
		const QJsonObject face = faces[key].toObject();
		const QJsonArray ids = face["lines"].toArray();

		list<shared_ptr<scLineQtVisual>> faceLineList;
		for (const auto& id : ids)
		{
			const string i = id.toString().toStdString();
			faceLineList.push_back(dynamic_pointer_cast<scLineQtVisual>(ShapeMap[i]));
		}

		const shared_ptr<scFaceQtVisual> newFace = make_shared<scFaceQtVisual>(faceLineList, mCoordinateHelper);
		const string id = key.toStdString();

		ShapeMap[id] = newFace;
		mFaceList.push_back(newFace);
	}

	for (const auto& id : orders)
	{
		const string i = id.toString().toStdString();
		mDrawShapeList.push_back(ShapeMap[i]);
	}
}

void scScene::ClearData()
{
	mVertexList.clear();
	mLineList.clear();
	mFaceList.clear();

	mDrawShapeList.clear();
}

int scScene::GetVertexCreatedCount() const
{
	return mVertexCreatedCount;
}
