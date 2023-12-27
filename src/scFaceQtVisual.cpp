#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scFaceData.h"
#include "scLineQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scRotateControlVertexQtVisual.h"

#include <qDebug>
#include <QVector3D>

using namespace std;

scFaceQtVisual::scFaceQtVisual(
	const list<shared_ptr<scLineQtVisual>>& lineList,
	const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
		: scShapeQtVisual(SHAPE_TYPE::FACE, coordinateHelper)
{
	// Set the lines.
	mFaceData = make_shared<scFaceData>();
	for (const auto& line : lineList)
	{
		mFaceData->AddLineData(line->mLineData);
	}

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

void scFaceQtVisual::ScaleFace(double dx, double dy, double transX, double transY)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyScaleXY(dx, dy, transX, transY);
	}
}

void scFaceQtVisual::RotateFace(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scBoundingBox box = MakeBoundingBox();

	scVector2D pp = mCoordinateHelper->CameraToLocal(prevMousePos.x(), prevMousePos.y());
	scVector2D tt = mCoordinateHelper->CameraToLocal(targetMousePos.x(), targetMousePos.y());

	QPointF A = { box.center.x, box.center.y };
	QPointF B = { pp.x, pp.y };
	QPointF C = { tt.x, tt.y };

	QLineF AB(A, B);
	QLineF BC(B, C);
	QLineF CA(C, A);

	double a = BC.length();
	double b = AB.length();
	double c = CA.length();

	/*if (b * c == 0.0)
		return;*/

	qDebug() << b * c;

	QVector3D v1(B - A);
	QVector3D v2(C - A);

	double crossZ = QVector3D::crossProduct(v1, v2).z();
	double dot = QPointF::dotProduct(B - A, C - A);

	/*double a = sqrt(QPointF::dotProduct(prevMousePos, targetMousePos));
	double b = sqrt(QPointF::dotProduct(prevMousePos, mCenter));
	double c = sqrt(QPointF::dotProduct(targetMousePos, mCenter));*/

	double sinX = crossZ / (b * c);
	double cosX = dot / (b * c);

	//qDebug() << asin(sinX) / 3.14 * 360.0;

	//qDebug() << (angle / 3.14) * 360.0;


	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyRotateXY(sinX, cosX, box.center.x, box.center.y);
	}

	mRotateControlVertex->mVertexData->GetTransform().MultiplyRotateXY(sinX, cosX, box.center.x, box.center.y);
}

scBoundingBox scFaceQtVisual::MakeBoundingBox()
{
	scBoundingBox boundingBox;

	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = DBL_MIN;
	double maxY = DBL_MIN;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToLocal(
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

	boundingBox.center = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };

	return boundingBox;
}
