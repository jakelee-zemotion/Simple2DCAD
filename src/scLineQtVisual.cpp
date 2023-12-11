#include "scLineQtVisual.h"
#include <qDebug>

using namespace std;

scLineQtVisual::scLineQtVisual(shared_ptr<scVertexQtVisual>& startVertex, shared_ptr<scVertexQtVisual>& endVertex)
{
	mLineData.SetStartVertex(startVertex);
	mLineData.SetEndVertex(endVertex);
}

scLineQtVisual::~scLineQtVisual()
{
}

//QPointF scQtLine::GetStartVertex()
//{
//	return QPointF(mLineData.GetStartX(), mLineData.GetStartY());
//}
//
//QPointF scQtLine::GetEndVertex()
//{
//	return QPointF(mLineData.GetEndX(), mLineData.GetEndY());
//}

QLineF scLineQtVisual::MakeQLineF()
{
	return 
		QLineF(
			{ mLineData.GetStartX(), mLineData.GetStartY() },
			{ mLineData.GetEndX(), mLineData.GetEndY() });
}

void scLineQtVisual::Paint(QPainter& painter)
{
	QPen pen(Qt::blue);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.drawLine(this->MakeQLineF());


	

}

bool scLineQtVisual::HitTest(QPointF& currMousePos)
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
