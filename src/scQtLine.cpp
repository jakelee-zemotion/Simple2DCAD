#include "scQtLine.h"

using namespace std;

scQtLine::scQtLine(shared_ptr<scQtVertex>& startVertex, shared_ptr<scQtVertex>& endVertex)
{
	mLineData.SetStartVertex(startVertex);
	mLineData.SetEndVertex(endVertex);
}

scQtLine::~scQtLine()
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

QLineF scQtLine::MakeQLineF()
{
	return 
		QLineF(
			{ mLineData.GetStartX(), mLineData.GetStartY() },
			{ mLineData.GetEndX(), mLineData.GetEndY() });
}

void scQtLine::Paint(QPainter& painter)
{
	QPen pen(Qt::blue);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.drawLine(this->MakeQLineF());
}

void scQtLine::HitTest(QPointF& currMousePos)
{
}
