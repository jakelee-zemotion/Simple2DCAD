#include "scLineQtVisual.h"

#include "scVertexQtVisual.h"
#include "scLineData.h"
#include "scCoordinateHelper.h"

#include <qDebug>

using namespace std;

scLineQtVisual::scLineQtVisual(
	SHAPE_TYPE shapeType,
	const shared_ptr<scVertexQtVisual>& startVertex, 
	const shared_ptr<scVertexQtVisual>& endVertex,
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(shapeType, coordinateHelper)
{
	// Set the vertices.
	mLineData = make_shared<scLineData>();
	mLineData->SetStartVertex(startVertex->GetVertexData());
	mLineData->SetEndVertex(endVertex->GetVertexData());

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::black;
	mShapeColors[static_cast<int>(COLOR_TYPE::PUT_ON)] = Qt::red;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::blue;
}

scLineQtVisual::~scLineQtVisual()
{
	qDebug() << "Line" << mShapeID.Get() << " Destruction";
}

QLineF scLineQtVisual::MakeQLineF()
{
	pair<double, double> localStart =
		mCoordinateHelper->WorldToCamera(mLineData->GetStartX(), mLineData->GetStartY(),
			mLineData->GetStartTransform());

	pair<double, double> localEnd =
		mCoordinateHelper->WorldToCamera(mLineData->GetEndX(), mLineData->GetEndY(),
			mLineData->GetEndTransform());

	return
		QLineF(
			{ localStart.first, localStart.second },
			{ localEnd.first, localEnd.second });
}

void scLineQtVisual::Move(double dx, double dy)
{
	pair<double, double> screenStartCoord = 
		mCoordinateHelper->WorldToScreen(mLineData->GetStartX(), mLineData->GetStartY());

	pair<double, double> screenEndCoord =
		mCoordinateHelper->WorldToScreen(mLineData->GetEndX(), mLineData->GetEndY());

	screenStartCoord.first += dx;
	screenStartCoord.second += dy;

	screenEndCoord.first += dx;
	screenEndCoord.second += dy;

	pair<double, double> worldStartCoord =
		mCoordinateHelper->ScreenToWorld(screenStartCoord.first, screenStartCoord.second);

	pair<double, double> worldEndCoord =
		mCoordinateHelper->ScreenToWorld(screenEndCoord.first, screenEndCoord.second);

	mLineData->SetStartVertex(worldStartCoord.first, worldStartCoord.second);
	mLineData->SetEndVertex(worldEndCoord.first, worldEndCoord.second);
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
