#include "scFaceQtVisual.h"

using namespace std;

scFaceQtVisual::scFaceQtVisual(const QRect& viewportSize)
	: scShapeQtVisual(viewportSize)
{
	mFaceData = make_shared<scFaceData>();
}

scFaceQtVisual::~scFaceQtVisual()
{
}

std::vector<QPointF>& scFaceQtVisual::MakeQPolygonF()
{
	mPolyVertices.clear();
	mPolyVertices.reserve(mFaceData->LineListSize());

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		QPointF endVertex =
		{
			mFaceData->GetLineEndX(),
			mFaceData->GetLineEndY()
		};
		mPolyVertices.push_back(endVertex);
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

	painter.drawPolygon(this->MakeQPolygonF().data(), this->MakeQPolygonF().size());
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	return false;
}
