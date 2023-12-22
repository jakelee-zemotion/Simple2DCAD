#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scFaceData.h"

#include <qDebug>

using namespace std;

scFaceQtVisual::scFaceQtVisual(
	const list<shared_ptr<scLineData>>& lineList, 
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	: scShapeQtVisual(SHAPE_TYPE::FACE, coordinateHelper)
{
	// Set the lines.
	mFaceData = make_shared<scFaceData>(lineList);

	// Set the colors.
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::gray;
	mShapeColors[static_cast<int>(COLOR_TYPE::HIGHTLIGHT)] = Qt::darkGray;
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
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToCamera(
				mFaceData->GetLineStartX(), mFaceData->GetLineStartY(), mFaceData->GetStartTransform());

		lineList.push_back({ cameraStartCoord.x, cameraStartCoord.y });
	}

	return QPolygonF(lineList);
}

void scFaceQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
			targetMousePos.x(), targetMousePos.y(), mFaceData->GetStartTransform());

		scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
			prevMousePos.x(), prevMousePos.y(), mFaceData->GetStartTransform());

		double dx = targetWorldCoord.x - prevWorldCoord.x;
		double dy = targetWorldCoord.y - prevWorldCoord.y;

		mFaceData->AddDxDyToLineStart(dx, dy);
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

	/*pen.setColor(Qt::red);
	pen.setWidth(1);
	pen.setStyle(Qt::DotLine);
	painter.setPen(pen);

	painter.setBrush(Qt::NoBrush);

	QRectF qr = qp.boundingRect();
	painter.drawPolygon(qr);*/
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

scBoundingBox scFaceQtVisual::GetBoundingBox()
{
	scBoundingBox boundingBox;

	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = DBL_MIN;
	double maxY = DBL_MIN;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToCamera(
			mFaceData->GetLineStartX(), mFaceData->GetLineStartY(), mFaceData->GetStartTransform());

		minX = min(minX, cameraStartCoord.x);
		maxX = max(maxX, cameraStartCoord.x);

		minY = min(minY, cameraStartCoord.y);
		maxY = max(maxY, cameraStartCoord.y);
	}

	constexpr double offset = 10.0;

	boundingBox.topLeft     = { minX - offset, minY - offset };
	boundingBox.topRight    = { maxX + offset, minY - offset };
	boundingBox.bottomLeft  = { minX - offset, maxY + offset };
	boundingBox.bottomRight = { maxX + offset, maxY + offset };

	return boundingBox;
}
