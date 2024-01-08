#include "scLineQtVisual.h"

// qt
#include <QDebug>
#include <QPainter>

// Simple2DCAD
#include "scVertexQtVisual.h"
#include "scLineData.h"
#include "scCoordinateHelper.h"

using namespace std;

scLineQtVisual::scLineQtVisual(const shared_ptr<scVertexQtVisual>& startVertex, const shared_ptr<scVertexQtVisual>& endVertex, const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scShapeQtVisual(scShapeType::LINE, coordinateHelper)
{
	// Set the vertices.
	mLineData = make_shared<scLineData>();
	mLineData->SetStartVertex(startVertex->mVertexData);
	mLineData->SetEndVertex(endVertex->mVertexData);

	// Set the colors.
	mShapeColors[static_cast<int>(scColorType::DEFAULT)] = Qt::darkMagenta;
	mShapeColors[static_cast<int>(scColorType::HIGHTLIGHT)] = Qt::red;
	mShapeColors[static_cast<int>(scColorType::SELECT)] = Qt::blue;
}

QLineF scLineQtVisual::MakeQLineF()
{
	const scVector2D cameraStart = mCoordinateHelper->WorldToCamera(mLineData->GetStartPos(), mLineData->GetStartTransform());
	const scVector2D cameraEnd = mCoordinateHelper->WorldToCamera(mLineData->GetEndPos(), mLineData->GetEndTransform());

	return QLineF({ cameraStart.x, cameraStart.y }, { cameraEnd.x, cameraEnd.y });
}

void scLineQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	const scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(targetMousePos, mLineData->GetStartTransform());
	const scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(prevMousePos, mLineData->GetStartTransform());
	const scVector2D delta = targetWorldCoord - prevWorldCoord;

	mLineData->AddDeltaToStart(delta);
	mLineData->AddDeltaToEnd(delta);
}

void scLineQtVisual::Paint(QPainter& painter)
{
	const Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(color);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.drawLine(this->MakeQLineF());
}

bool scLineQtVisual::HitTest(const scVector2D& currMousePos)
{
	QLineF normal = this->MakeQLineF().normalVector();
	QLineF normal2 = this->MakeQLineF().normalVector();
	const QPointF origin(currMousePos.x, currMousePos.y);

	// Two normal vectors are drawn in both directions around the origin.
	normal.setP2(normal.p2() - normal.p1() + origin);
	normal.setP1(origin);

	normal2.setP2(normal2.p1() - normal2.p2() + origin);
	normal2.setP1(origin);

	normal.setLength(mHitSize);
	normal2.setLength(mHitSize);

	// Combine two normal vectors.
	const QLineF centralNormal(normal.p2(), normal2.p2());

	return centralNormal.intersects(this->MakeQLineF()) == QLineF::BoundedIntersection;
}

scShapeID scLineQtVisual::GetID() const
{
	return mLineData->GetID();
}

scShapeID scLineQtVisual::GetStartVertexID()
{
	return mLineData->GetStartID();
}

scShapeID scLineQtVisual::GetEndVertexID()
{
	return mLineData->GetEndID();
}