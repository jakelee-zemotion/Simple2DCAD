#include "scFaceQtVisual.h"

#include <qDebug>

using namespace std;

scFaceQtVisual::scFaceQtVisual(
	const list<shared_ptr<scLineData>>& lineList, 
	const QRect& viewportSize)
	: scShapeQtVisual(viewportSize)
{
	// Set the lines.
	mFaceData = make_shared<scFaceData>(lineList);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::gray;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::darkGray;
	mShapeColors[static_cast<int>(COLOR_TYPE::CLICK)] = Qt::cyan;
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
		pair<double, double> screenStartCoord =
			WorldToScreen(mFaceData->GetLineStartX(), mFaceData->GetLineStartY());

		mPolyVertices.push_back({ screenStartCoord.first, screenStartCoord.second });
	}

	return mPolyVertices;
}

void scFaceQtVisual::MoveShape(double dx, double dy)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		pair<double, double> screenStartCoord =
			WorldToScreen(mFaceData->GetLineStartX(), mFaceData->GetLineStartY());

		screenStartCoord.first += dx;
		screenStartCoord.second += dy;

		pair<double, double> worldStartCoord =
			ScreenToWorld(screenStartCoord.first, screenStartCoord.second);

		mFaceData->SetLineStart(worldStartCoord.first, worldStartCoord.second);
	}

}

void scFaceQtVisual::Paint(QPainter& painter)
{
	Qt::GlobalColor color = mShapeColors[static_cast<int>(mShapeColorType)];

	QPen pen(Qt::black);
	pen.setWidth(3);
	painter.setPen(pen);

	QBrush brush(color);
	painter.setBrush(brush);

	painter.drawPolygon(this->MakeQPolygonF().data(), this->MakeQPolygonF().size());
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	return true;
}
