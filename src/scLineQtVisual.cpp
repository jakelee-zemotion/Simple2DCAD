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


	QLineF normal = this->MakeQLineF().normalVector();
	QPointF aaa(100.0, 100.0);
	painter.drawPoint(aaa);

	normal.setP2(normal.p2() - normal.p1() + aaa);
	normal.setP1(aaa);

	normal.setLength(20.0);

	qDebug() << normal;
	QPen pen2(Qt::red);
	pen2.setWidth(3);
	painter.setPen(pen2);
	painter.drawLine(normal);

}

bool scLineQtVisual::HitTest(QPointF& currMousePos)
{

	return false;
}
