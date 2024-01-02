#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scFaceData.h"
#include "scVertexQtVisual.h"
#include "scLineQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scRotateControlVertexQtVisual.h"
#include "scCenterControlVertexQtVisual.h"

#include <qDebug>
#include <QPainter>
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

	ResetControlVertices();
}

scFaceQtVisual::~scFaceQtVisual()
{
	qDebug() << "Face" << mShapeID << " Destruction";
}

QPolygonF scFaceQtVisual::MakeQPolygonF()
{
	QList<QPointF> lineList;

	// Copy data using custom iteration.
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToCamera(
				mFaceData->GetLineStartPos(), mFaceData->GetStartTransform());

		lineList.push_back({ cameraStartCoord.x, cameraStartCoord.y });
	}

	return QPolygonF(lineList);
}

void scFaceQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
			targetMousePos, mFaceData->GetStartTransform());

		scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
			prevMousePos, mFaceData->GetStartTransform());

		scVector2D delta = targetWorldCoord - prevWorldCoord;

		mFaceData->AddDeltaToLineStart(delta);
	}


	for (const auto& ss : mControlVertexVector)
	{
		ss->Move(targetMousePos, prevMousePos);
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

bool scFaceQtVisual::HitTest(const scVector2D& currMousePos)
{
	QPointF currQPointF = { currMousePos.x, currMousePos.y };

	if (this->MakeQPolygonF().containsPoint(currQPointF, Qt::OddEvenFill))
	{
		return true;
	}

	return false;
}

void scFaceQtVisual::ScaleFace(const scVector2D& d, const scVector2D& diagLocalCoord, const BOX_POSITION& boxPos, double angle)
{
	


	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyScaleXY(d.x, d.y, diagLocalCoord.x, diagLocalCoord.y, angle);
	}


	for (const auto& ss : mControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyScaleXY(d.x, d.y, diagLocalCoord.x, diagLocalCoord.y, angle);
	}
}

void scFaceQtVisual::RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyRotateXY(angle, targetMousePos.x, targetMousePos.y);
	}


	for (const auto& ss : mControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyRotateXY(angle, targetMousePos.x, targetMousePos.y);
	}
}

void scFaceQtVisual::ResetControlVertices()
{
	ResetBoundingBox();


	mControlVertexVector.clear();

	scVector2D bb;



	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.topLeft);
	mControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::TOP_LEFT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.topRight);
	mControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::TOP_RIGHT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.bottomRight);
	mControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::BOTTOM_RIGHT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.bottomLeft);
	mControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::BOTTOM_LEFT, mCoordinateHelper) });




	bb = mCoordinateHelper->LocalToCamera({ mBoundingBox.center.x, mBoundingBox.topLeft.y });
	mControlVertexVector.push_back({ make_shared<scRotateControlVertexQtVisual>(this, bb, mCoordinateHelper) });



	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.center);
	mControlVertexVector.push_back({ make_shared<scCenterControlVertexQtVisual>(this, bb, mCoordinateHelper) });
}

void scFaceQtVisual::ResetBoundingBox()
{
	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = -DBL_MAX;
	double maxY = -DBL_MAX;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToLocal(
			mFaceData->GetLineStartPos(), mFaceData->GetStartTransform());

		minX = min(minX, cameraStartCoord.x);
		maxX = max(maxX, cameraStartCoord.x);

		minY = min(minY, cameraStartCoord.y);
		maxY = max(maxY, cameraStartCoord.y);
	}

	constexpr double offset = 10.0;

	mBoundingBox.topLeft     = { minX - offset, minY - offset };
	mBoundingBox.topRight    = { maxX + offset, minY - offset };
	mBoundingBox.bottomLeft  = { minX - offset, maxY + offset };
	mBoundingBox.bottomRight = { maxX + offset, maxY + offset };

	mBoundingBox.center = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}
