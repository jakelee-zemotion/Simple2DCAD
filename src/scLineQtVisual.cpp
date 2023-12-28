#include "scLineQtVisual.h"

#include "scVertexQtVisual.h"
#include "scLineData.h"
#include "scCoordinateHelper.h"

#include <qDebug>

using namespace std;

scLineQtVisual::scLineQtVisual(
	const shared_ptr<scVertexQtVisual>& startVertex, 
	const shared_ptr<scVertexQtVisual>& endVertex,
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(SHAPE_TYPE::LINE, coordinateHelper)
{
	// Set the vertices.
	mLineData = make_shared<scLineData>();
	mLineData->SetStartVertex(startVertex->mVertexData);
	mLineData->SetEndVertex(endVertex->mVertexData);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::black;
	mShapeColors[static_cast<int>(COLOR_TYPE::HIGHTLIGHT)] = Qt::red;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::blue;
}

scLineQtVisual::~scLineQtVisual()
{
	qDebug() << "Line" << mShapeID.Get() << " Destruction";
}

QLineF scLineQtVisual::MakeQLineF()
{
	scVector2D cameraStart = mCoordinateHelper->WorldToCamera(
			mLineData->GetStartX(), mLineData->GetStartY(), mLineData->GetStartTransform());

	scVector2D cameraEnd = mCoordinateHelper->WorldToCamera(
			mLineData->GetEndX(), mLineData->GetEndY(), mLineData->GetEndTransform());

	return
		QLineF(
			{ cameraStart.x, cameraStart.y },
			{ cameraEnd.x, cameraEnd.y });
}

void scLineQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
		targetMousePos.x, targetMousePos.y, mLineData->GetStartTransform());

	scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
		prevMousePos.x, prevMousePos.y, mLineData->GetStartTransform());

	double dx = targetWorldCoord.x - prevWorldCoord.x;
	double dy = targetWorldCoord.y - prevWorldCoord.y;

	mLineData->AddDxDyToStart(dx, dy);
	mLineData->AddDxDyToEnd(dx, dy);
}

void scLineQtVisual::Paint(QPainter& painter)
{
	Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(color);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.drawLine(this->MakeQLineF());
}

bool scLineQtVisual::HitTest(const scVector2D& currMousePos)
{
	QLineF normal = this->MakeQLineF().normalVector();
	QLineF normal2 = this->MakeQLineF().normalVector();
	QPointF aaa(currMousePos.x, currMousePos.y);

	normal.setP2(normal.p2() - normal.p1() + aaa);
	normal.setP1(aaa);

	normal2.setP2(normal2.p1() - normal2.p2() + aaa);
	normal2.setP1(aaa);

	normal.setLength(mHitSize);
	normal2.setLength(mHitSize);

	QLineF centralNormal(normal.p2(), normal2.p2());

	if (centralNormal.intersects(this->MakeQLineF()) == QLineF::BoundedIntersection)
	{
		return true;
	}

	return false;
}