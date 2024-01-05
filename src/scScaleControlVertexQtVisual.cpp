#include "scScaleControlVertexQtVisual.h"

// qt
#include <QTransform>

// Simple2DCAD
#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

using namespace std;

scScaleControlVertexQtVisual::scScaleControlVertexQtVisual(scFaceQtVisual* face, const scVector2D& pos, const double& angleSum, const scBoxPosition& boxPos, 
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scControlVertexQtVisual(face, pos, coordinateHelper), mBoxPos(boxPos), mAngleSum(angleSum)
{
	mShapeType = scShapeType::SCALE_CONTROL_VERTEX;
}

scScaleControlVertexQtVisual::~scScaleControlVertexQtVisual()
{
}

void scScaleControlVertexQtVisual::ScaleFace(const scVector2D& scale, const scVector2D& trans, const double angle)
{
	mParentFace->ScaleFace(scale, trans, angle);
}

void scScaleControlVertexQtVisual::Paint(QPainter& painter)
{
	string fileDir = SC_IMAGE_DIRECTORY;
	fileDir += "vertex/scScaleControlVertex.png";

	const double width = 60.0;
	QImage image(QString::fromStdString(fileDir));

	const double radianAngle = mAngleSum / 3.1415196535 * 180.0;

	switch (mBoxPos)
	{
		case scBoxPosition::TOP_LEFT:
			image = image.transformed(QTransform().rotate(135.0 + radianAngle));
			break;

		case scBoxPosition::TOP_RIGHT:
			image = image.transformed(QTransform().rotate(-135.0 + radianAngle));
			break;

		case scBoxPosition::BOTTOM_RIGHT:
			image = image.transformed(QTransform().rotate(-45.0 + radianAngle));
			break;

		case scBoxPosition::BOTTOM_LEFT:
			image = image.transformed(QTransform().rotate(45.0 + radianAngle));
			break;
	}

	const QRectF imageRect(this->MakeQPointF().x() - width / 2.0, this->MakeQPointF().y() - width / 2.0, width, width);

	painter.drawImage(imageRect, image);
}

scBoxPosition scScaleControlVertexQtVisual::GetBoxPosition() const
{
	return mBoxPos;
}
