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
}

scFaceQtVisual::~scFaceQtVisual()
{
}

QPolygonF scFaceQtVisual::MakeQPolygonF()
{
	QList<QPointF> lineList;

	// Copy data using custom iteration.
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToCamera(
				mFaceData->GetLineStartPos(), mFaceData->GetLineStartTransform());

		lineList.push_back({ cameraStartCoord.x, cameraStartCoord.y });
	}

	return QPolygonF(lineList);
}

void scFaceQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
			targetMousePos, mFaceData->GetLineStartTransform());

		scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
			prevMousePos, mFaceData->GetLineStartTransform());

		scVector2D delta = targetWorldCoord - prevWorldCoord;

		mFaceData->AddDeltaToLineStart(delta);
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

scShapeID scFaceQtVisual::GetID() const
{
	return mFaceData->GetID();
}

void scFaceQtVisual::ScaleFace(const scVector2D& d, const scVector2D& diagLocalCoord, const BOX_POSITION& boxPos, double angle)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetLineStartTransform().MultiplyScaleXY(d.x, d.y, diagLocalCoord.x, diagLocalCoord.y, angle);
	}
}

void scFaceQtVisual::RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetLineStartTransform().MultiplyRotateXY(angle, targetMousePos.x, targetMousePos.y);
	}
}

void scFaceQtVisual::SetTransformToXY()
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D localCoord = mCoordinateHelper->WorldToLocal(
			mFaceData->GetLineStartPos(), mFaceData->GetLineStartTransform());

		scVector2D worldCoord = mCoordinateHelper->ScreenToWorld(localCoord);

		mFaceData->SetLineStartPos(worldCoord);
		mFaceData->GetLineStartTransform().ResetMatrix();
	}
}

std::list<scShapeID> scFaceQtVisual::GetLineStartIDs() const
{
	list<scShapeID> ids;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		ids.push_back(mFaceData->GetLineStartID());
	}

	return ids;
}


scBoundingBox scFaceQtVisual::MakeBoundingBox()
{
	scBoundingBox box;

	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = -DBL_MAX;
	double maxY = -DBL_MAX;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D cameraStartCoord = mCoordinateHelper->WorldToLocal(
			mFaceData->GetLineStartPos(), mFaceData->GetLineStartTransform());

		minX = min(minX, cameraStartCoord.x);
		maxX = max(maxX, cameraStartCoord.x);

		minY = min(minY, cameraStartCoord.y);
		maxY = max(maxY, cameraStartCoord.y);
	}

	constexpr double offset = 10.0;

	box.topLeft     = { minX - offset, minY - offset };
	box.topRight    = { maxX + offset, minY - offset };
	box.bottomLeft  = { minX - offset, maxY + offset };
	box.bottomRight = { maxX + offset, maxY + offset };

	box.center = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };

	return box;
}
