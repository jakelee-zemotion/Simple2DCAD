#include "scFaceQtVisual.h"

// qt
#include <QDebug>
#include <QPainter>
#include <QVector3D>

// Simple2DCAD
#include "scCoordinateHelper.h"
#include "scFaceData.h"
#include "scLineQtVisual.h"

using namespace std;

scFaceQtVisual::scFaceQtVisual(const list<shared_ptr<scLineQtVisual>>& lineList, const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scShapeQtVisual(scShapeType::FACE, coordinateHelper)
{
	// Set the lines.
	mFaceData = make_shared<scFaceData>();
	for (const auto& line : lineList)
	{
		mFaceData->AddLineData(line->mLineData);
	}

	// Set the colors.
	mShapeColors[static_cast<int>(scColorType::DEFAULT)] = Qt::gray;
	mShapeColors[static_cast<int>(scColorType::HIGHTLIGHT)] = Qt::darkGray;
	mShapeColors[static_cast<int>(scColorType::SELECT)] = Qt::cyan;
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
		const scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(targetMousePos, mFaceData->GetLineStartTransform());
		const scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(prevMousePos, mFaceData->GetLineStartTransform());
		const scVector2D delta = targetWorldCoord - prevWorldCoord;

		mFaceData->AddDeltaToLineStart(delta);
	}
}

void scFaceQtVisual::Paint(QPainter& painter)
{
	QColor color = mShapeColors[static_cast<int>(mShapeColorType)];
	color.setAlphaF(0.5);

	QPen pen(Qt::black);
	pen.setWidth(3);
	painter.setPen(pen);

	QBrush brush(color);
	painter.setBrush(brush);

	painter.drawPolygon(this->MakeQPolygonF());
}

bool scFaceQtVisual::HitTest(const scVector2D& currMousePos)
{
	const QPointF currQPointF = { currMousePos.x, currMousePos.y };

	return this->MakeQPolygonF().containsPoint(currQPointF, Qt::OddEvenFill);
}

scShapeID scFaceQtVisual::GetID() const
{
	return mFaceData->GetID();
}

void scFaceQtVisual::ScaleFace(const scVector2D& scale, const scVector2D& trans, const double angle)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetLineStartTransform().MultiplyScaleXY(scale, trans, angle);
	}
}

void scFaceQtVisual::RotateFace(const scVector2D& trans, const double angle)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetLineStartTransform().MultiplyRotateXY(trans, angle);
	}
}

void scFaceQtVisual::SetTransformToXY()
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		const scVector2D localCoord = mCoordinateHelper->WorldToLocal(mFaceData->GetLineStartPos(), mFaceData->GetLineStartTransform());
		const scVector2D worldCoord = mCoordinateHelper->ScreenToWorld(localCoord);

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
		const scVector2D cameraStartCoord = mCoordinateHelper->WorldToLocal(mFaceData->GetLineStartPos(), mFaceData->GetLineStartTransform());

		minX = min(minX, cameraStartCoord.x);
		maxX = max(maxX, cameraStartCoord.x);

		minY = min(minY, cameraStartCoord.y);
		maxY = max(maxY, cameraStartCoord.y);
	}

	const double offset = 0.0;

	box.topLeft     = { minX - offset, minY - offset };
	box.topRight    = { maxX + offset, minY - offset };
	box.bottomLeft  = { minX - offset, maxY + offset };
	box.bottomRight = { maxX + offset, maxY + offset };

	box.center = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };

	return box;
}
