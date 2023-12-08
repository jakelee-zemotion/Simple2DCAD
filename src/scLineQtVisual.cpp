#include "scLineQtVisual.h"

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
	return false;
}
