#include "scFaceQtVisual.h"

#include <qDebug>

using namespace std;

scFaceQtVisual::scFaceQtVisual(
	const list<shared_ptr<scLineData>>& lineList, 
	const QRect& viewportSize)
	: scShapeQtVisual(viewportSize)
{
	mFaceData = make_shared<scFaceData>(lineList);
}

scFaceQtVisual::~scFaceQtVisual()
{
	//qDebug() << "Face" << mShapeID.Get() << " Destruction";
}

std::vector<QPointF>& scFaceQtVisual::MakeQPolygonF()
{
	mPolyVertices.clear();
	mPolyVertices.reserve(mFaceData->LineListSize());

	// Copy data using custom iteration.
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		pair<double, double> screenStart =
			WorldToScreen(mFaceData->GetLineStartX(), mFaceData->GetLineStartY());

		mPolyVertices.push_back({ screenStart.first, screenStart.second });
	}

	return mPolyVertices;
}

void scFaceQtVisual::MoveShape(double dx, double dy)
{
}

void scFaceQtVisual::Paint(QPainter& painter)
{
	QPen pen(mPenColor);
	pen.setWidth(3);
	painter.setPen(pen);

	QBrush brush(Qt::red);
	painter.setBrush(brush);

	painter.drawPolygon(this->MakeQPolygonF().data(), this->MakeQPolygonF().size());
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	return false;
}
