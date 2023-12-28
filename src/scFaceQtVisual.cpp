#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scFaceData.h"
#include "scVertexQtVisual.h"
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

	ResetControlVertices();
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

void scFaceQtVisual::Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		scVector2D targetWorldCoord = mCoordinateHelper->CameraToWorld(
			targetMousePos.x, targetMousePos.y, mFaceData->GetStartTransform());

		scVector2D prevWorldCoord = mCoordinateHelper->CameraToWorld(
			prevMousePos.x, prevMousePos.y, mFaceData->GetStartTransform());

		double dx = targetWorldCoord.x - prevWorldCoord.x;
		double dy = targetWorldCoord.y - prevWorldCoord.y;

		mFaceData->AddDxDyToLineStart(dx, dy);
	}

	scVector2D targetScreenCoord = mCoordinateHelper->CameraToLocal(
		targetMousePos.x, targetMousePos.y);
	scVector2D prevScreenCoord = mCoordinateHelper->CameraToLocal(
		prevMousePos.x, prevMousePos.y);

	scVector2D dist = targetScreenCoord - prevScreenCoord;

	mBoundingBox.center += dist;

	QPointF aa = { targetMousePos.x, targetMousePos.y };
	QPointF bb = { prevMousePos.x, prevMousePos.y };

	mRotateControlVertex->MoveControlVertexDirectly(aa, bb);

	for (const auto& ss : mScaleControlVertexVector)
	{
		ss->MoveControlVertexDirectly(aa, bb);
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


	scVector2D centers = mCoordinateHelper->LocalToCamera(mBoundingBox.center.x, mBoundingBox.center.y);
	QPointF center = { centers.x, centers.y };
	painter.drawPoint(center);


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

void scFaceQtVisual::ScaleFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, const BOX_POSITION& boxPos)
{
	int diagIdx = (static_cast<int>(boxPos) + 2) % 4;

	shared_ptr<scScaleControlVertexQtVisual> diagVertex = mScaleControlVertexVector[diagIdx];

	scVector2D diagLocalCoord = mCoordinateHelper->WorldToLocal(diagVertex->mVertexData->GetX(), diagVertex->mVertexData->GetY(), diagVertex->mVertexData->GetTransform());

	scVector2D targetLocalCoord = mCoordinateHelper->CameraToLocal(targetMousePos.x, targetMousePos.y);
	scVector2D prevLocalCoord = mCoordinateHelper->CameraToLocal(prevMousePos.x, prevMousePos.y);

	targetLocalCoord -= diagLocalCoord;
	prevLocalCoord -= diagLocalCoord;


	double angle = diagVertex->mVertexData->GetTransform().angle;
	scMatrix2D inverseRotateMatrix = MatrixHelper::InverseRotateMatrix(angle);
	scMatrix2D RotateMatrix = MatrixHelper::RotateMatrix(angle);

	targetLocalCoord = (inverseRotateMatrix * targetLocalCoord);
	prevLocalCoord = (inverseRotateMatrix * prevLocalCoord);

	double dx = targetLocalCoord.x / prevLocalCoord.x;
	double dy = targetLocalCoord.y / prevLocalCoord.y;

	mBoundingBox.center -= diagLocalCoord;
	scMatrix2D scaleMatrix = MatrixHelper::ScaleMatrix(dx, dy);
	mBoundingBox.center = (RotateMatrix * scaleMatrix * inverseRotateMatrix * mBoundingBox.center);
	mBoundingBox.center += diagLocalCoord;

	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyScaleXY(dx, dy, diagLocalCoord.x, diagLocalCoord.y, angle);
	}

	mRotateControlVertex->mVertexData->GetTransform().MultiplyScaleXY(dx, dy, diagLocalCoord.x, diagLocalCoord.y, angle);

	for (const auto& ss : mScaleControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyScaleXY(dx, dy, diagLocalCoord.x, diagLocalCoord.y, angle);
	}
}

void scFaceQtVisual::RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos)
{
	scVector2D pp = mCoordinateHelper->CameraToLocal(prevMousePos.x, prevMousePos.y);
	scVector2D tt = mCoordinateHelper->CameraToLocal(targetMousePos.x, targetMousePos.y);

	QPointF A = { mBoundingBox.center.x, mBoundingBox.center.y };
	QPointF B = { pp.x, pp.y };
	QPointF C = { tt.x, tt.y };

	QLineF AB(A, B);
	QLineF BC(B, C);
	QLineF CA(C, A);

	double a = BC.length();
	double b = AB.length();
	double c = CA.length();

	//qDebug() << b * c;

	if (b * c == 0.0)
		return;


	QVector3D v1(B - A);
	QVector3D v2(C - A);

	double crossZ = QVector3D::crossProduct(v1, v2).z();
	double dot = QPointF::dotProduct(B - A, C - A);

	double sinX = crossZ / (b * c);
	double cosX = dot / (b * c);



	for (mFaceData->ResetIter(); !mFaceData->IsIterEnd(); mFaceData->NextIter())
	{
		mFaceData->GetStartTransform().MultiplyRotateXY(sinX, cosX, mBoundingBox.center.x, mBoundingBox.center.y);
	}

	mRotateControlVertex->mVertexData->GetTransform().MultiplyRotateXY(sinX, cosX, mBoundingBox.center.x, mBoundingBox.center.y);

	for (const auto& ss : mScaleControlVertexVector)
	{
		ss->mVertexData->GetTransform().MultiplyRotateXY(sinX, cosX, mBoundingBox.center.x, mBoundingBox.center.y);
	}
}

void scFaceQtVisual::ResetControlVertices()
{
	ResetBoundingBox();


	mRotateControlVertex.reset();
	scVector2D bb = mCoordinateHelper->LocalToCamera(mBoundingBox.center.x, mBoundingBox.topLeft.y);

	mRotateControlVertex = make_shared<scRotateControlVertexQtVisual>(this, bb, mCoordinateHelper);


	mScaleControlVertexVector.clear();

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.topLeft.x, mBoundingBox.topLeft.y);
	mScaleControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::TOP_LEFT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.topRight.x, mBoundingBox.topRight.y);
	mScaleControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::TOP_RIGHT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.bottomRight.x, mBoundingBox.bottomRight.y);
	mScaleControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::BOTTOM_RIGHT, mCoordinateHelper) });

	bb = mCoordinateHelper->LocalToCamera(mBoundingBox.bottomLeft.x, mBoundingBox.bottomLeft.y);
	mScaleControlVertexVector.push_back({ make_shared<scScaleControlVertexQtVisual>(this, bb, BOX_POSITION::BOTTOM_LEFT, mCoordinateHelper) });
}

void scFaceQtVisual::ResetBoundingBox()
{
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

	mBoundingBox.topLeft     = { minX - offset, minY - offset };
	mBoundingBox.topRight    = { maxX + offset, minY - offset };
	mBoundingBox.bottomLeft  = { minX - offset, maxY + offset };
	mBoundingBox.bottomRight = { maxX + offset, maxY + offset };

	mBoundingBox.center = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}
