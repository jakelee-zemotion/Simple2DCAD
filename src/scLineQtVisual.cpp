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
	mLineData->SetStartVertex(startVertex->GetVertexData());
	mLineData->SetEndVertex(endVertex->GetVertexData());

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
	auto cameraStart = mCoordinateHelper->WorldToCamera(
			mLineData->GetStartX(), mLineData->GetStartY(), mLineData->GetStartTransform());

	auto cameraEnd = mCoordinateHelper->WorldToCamera(
			mLineData->GetEndX(), mLineData->GetEndY(), mLineData->GetEndTransform());

	return
		QLineF(
			{ cameraStart.first, cameraStart.second },
			{ cameraEnd.first, cameraEnd.second });
}

void scLineQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	auto targetWorldCoord = 
		mCoordinateHelper->CameraToWorld(targetMousePos.x(), targetMousePos.y(), mLineData->GetStartTransform());
	auto prevWorldCoord = 
		mCoordinateHelper->CameraToWorld(prevMousePos.x(), prevMousePos.y(), mLineData->GetStartTransform());

	double dx = targetWorldCoord.first - prevWorldCoord.first;
	double dy = targetWorldCoord.second - prevWorldCoord.second;

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

bool scLineQtVisual::HitTest(const QPointF& currMousePos)
{
	QLineF normal = this->MakeQLineF().normalVector();
	QLineF normal2 = this->MakeQLineF().normalVector();
	QPointF aaa(currMousePos);

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

std::shared_ptr<scLineData> scLineQtVisual::GetLineData() const
{
	return mLineData;
}
