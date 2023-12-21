#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scFaceData.h"

#include <qDebug>

using namespace std;

scFaceQtVisual::scFaceQtVisual(
	SHAPE_TYPE shapeType,
	const list<shared_ptr<scLineData>>& lineList, 
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	: scShapeQtVisual(shapeType, coordinateHelper)
{
	// Set the lines.
	mFaceData = make_shared<scFaceData>(lineList);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::gray;
	mShapeColors[static_cast<int>(COLOR_TYPE::PUT_ON)] = Qt::darkGray;
	mShapeColors[static_cast<int>(COLOR_TYPE::SELECT)] = Qt::cyan;
}

scFaceQtVisual::~scFaceQtVisual()
{
	//qDebug() << "Face" << mShapeID.Get() << " Destruction";
}

QPolygonF scFaceQtVisual::MakeQPolygonF()
{
	QList<QPointF> lineList;

	// Copy data using custom iteration.
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		auto localStartCoord =
			mCoordinateHelper->WorldToCamera(mFaceData->GetLineStartX(), mFaceData->GetLineStartY(),
				mFaceData->GetStartTransform());

		lineList.push_back({ localStartCoord.first, localStartCoord.second });
	}

	return QPolygonF(lineList);
}

void scFaceQtVisual::Move(double dx, double dy)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		pair<double, double> screenStartCoord =
			mCoordinateHelper->WorldToScreen(mFaceData->GetLineStartX(), mFaceData->GetLineStartY());

		screenStartCoord.first += dx;
		screenStartCoord.second += dy;

		pair<double, double> worldStartCoord =
			mCoordinateHelper->ScreenToWorld(screenStartCoord.first, screenStartCoord.second);

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

	QPolygonF qp = this->MakeQPolygonF();
	painter.drawPolygon(qp);

	pen.setWidth(1);
	pen.setStyle(Qt::DotLine);
	painter.setPen(pen);

	painter.setBrush(Qt::NoBrush);

	QRectF qr = qp.boundingRect();
	painter.drawPolygon(qr);
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	if (this->MakeQPolygonF().containsPoint(currMousePos, Qt::OddEvenFill))
	{
		return true;
	}

	return false;
}

void scFaceQtVisual::ScaleFace(double dx, double dy)
{
	QPointF center = this->MakeQPolygonF().boundingRect().center();

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyScaleXY(dx, dy);
	}
}

void scFaceQtVisual::RotateFace(double theta)
{
	QPointF center = this->MakeQPolygonF().boundingRect().center();

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		pair<double, double> screenStartCoord =
			mCoordinateHelper->WorldToScreen(mFaceData->GetLineStartX(), mFaceData->GetLineStartY());

		screenStartCoord.first -= center.x();
		screenStartCoord.second -= center.y();

		double cosT = cos(theta);
		double sinT = sin(theta);

		double x = screenStartCoord.first;
		double y = screenStartCoord.second;

		screenStartCoord.first = cosT * x - sinT * y;
		screenStartCoord.second = sinT * x + cosT * y;

		screenStartCoord.first += center.x();
		screenStartCoord.second += center.y();

		pair<double, double> worldStartCoord =
			mCoordinateHelper->ScreenToWorld(screenStartCoord.first, screenStartCoord.second);

		mFaceData->SetLineStart(worldStartCoord.first, worldStartCoord.second);
	}
}
