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

void scFaceQtVisual::ScaleFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, const BOX_POSITION& boxPos, double angle)
{
	int diagIdx = (static_cast<int>(boxPos) + 2) % 4;

	shared_ptr<scScaleControlVertexQtVisual> diagVertex = dynamic_pointer_cast<scScaleControlVertexQtVisual>(mControlVertexVector[diagIdx]);

	scVector2D diagLocalCoord = mCoordinateHelper->WorldToLocal(diagVertex->mVertexData->GetPos(), diagVertex->mVertexData->GetTransform());

	scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetMousePos);
	scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(prevMousePos);

	targetLocalCoord -= diagLocalCoord;
	prevLocalCoord -= diagLocalCoord;

	scMatrix2D inverseRotateMatrix = MatrixHelper::InverseRotateMatrix(angle);

	targetLocalCoord = (inverseRotateMatrix * targetLocalCoord);
	prevLocalCoord = (inverseRotateMatrix * prevLocalCoord);

	double dx = targetLocalCoord.x / prevLocalCoord.x;
	double dy = targetLocalCoord.y / prevLocalCoord.y;


	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyScaleXY(dx, dy, diagLocalCoord.x, diagLocalCoord.y, angle);
	}


	for (const auto& ss : mControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyScaleXY(dx, dy, diagLocalCoord.x, diagLocalCoord.y, angle);
	}
}

void scFaceQtVisual::RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	scVector2D BB = mCoordinateHelper->CameraToLocal(prevMousePos);
	scVector2D CC = mCoordinateHelper->CameraToLocal(targetMousePos);

	shared_ptr<scCenterControlVertexQtVisual> centerVertex = dynamic_pointer_cast<scCenterControlVertexQtVisual>(mControlVertexVector.back());
	scVector2D AA = mCoordinateHelper->WorldToLocal(centerVertex->mVertexData->GetPos(), centerVertex->mVertexData->GetTransform());

	double a = VectorHelper::length(BB, CC);
	double b = VectorHelper::length(AA, BB);
	double c = VectorHelper::length(CC, AA);

	//qDebug() << b * c;

	if (b * c == 0.0)
		return;

	double crossZ = VectorHelper::crossZ(BB - AA, CC - AA);
	double sinX = crossZ / (b * c);

	angle += asin(sinX);


	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyRotateXY(asin(sinX), AA.x, AA.y);
	}


	for (const auto& ss : mControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyRotateXY(asin(sinX), AA.x, AA.y);
	}
}

void scFaceQtVisual::ResetControlVertices()
{
	ResetBoundingBox();


	scVector2D bb;


	mControlVertexVector.clear();

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
