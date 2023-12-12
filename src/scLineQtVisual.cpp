#include "scLineQtVisual.h"
#include <qDebug>

using namespace std;

scLineQtVisual::scLineQtVisual(
	shared_ptr<scVertexQtVisual>& startVertex, 
	shared_ptr<scVertexQtVisual>& endVertex,
	const QRect& viewportSize)
: scShapeQtVisual(viewportSize)
{
	mLineData = make_shared<scLineData>();
	mLineData->SetStartVertex(startVertex->GetVertexData());
	mLineData->SetEndVertex(endVertex->GetVertexData());
}

scLineQtVisual::~scLineQtVisual()
{
}

QLineF scLineQtVisual::MakeQLineF()
{
	pair<double, double> screenStart =
		WorldToScreen(mLineData->GetStartX(), mLineData->GetStartY());

	pair<double, double> screenEnd =
		WorldToScreen(mLineData->GetEndX(), mLineData->GetEndY());

	return
		QLineF(
			{ screenStart.first, screenStart.second },
			{ screenEnd.first, screenEnd.second });
}

void scLineQtVisual::MoveShape(double dx, double dy)
{
	pair<double, double> screenStartCoord = 
		WorldToScreen(mLineData->GetStartX(), mLineData->GetStartY());

	pair<double, double> screenEndCoord =
		WorldToScreen(mLineData->GetEndX(), mLineData->GetEndY());

	screenStartCoord.first += dx;
	screenStartCoord.second += dy;

	screenEndCoord.first += dx;
	screenEndCoord.second += dy;

	pair<double, double> worldStartCoord =
		ScreenToWorld(screenStartCoord.first, screenStartCoord.second);

	pair<double, double> worldEndCoord =
		ScreenToWorld(screenEndCoord.first, screenEndCoord.second);

	mLineData->SetStartVertex(worldStartCoord.first, worldStartCoord.second);
	mLineData->SetEndVertex(worldEndCoord.first, worldEndCoord.second);
}

void scLineQtVisual::Paint(QPainter& painter)
{
	QPen pen(mPenColor);
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

	normal.setLength(10.0);
	normal2.setLength(10.0);

	QLineF centralNormal(normal.p2(), normal2.p2());

	if (centralNormal.intersects(this->MakeQLineF()) == QLineF::BoundedIntersection)
	{
		return true;
	}

	return false;
}
