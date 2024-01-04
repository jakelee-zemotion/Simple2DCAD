#include "scRotateControlVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"
#include "scVertexData.h"

#include <qDebug>

using namespace std;

scRotateControlVertexQtVisual::scRotateControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper)
{
	mShapeType = scShapeType::ROTATE_CONTROL_VERTEX;

	mShapeColors[static_cast<int>(scColorType::DEFAULT)] = Qt::darkGreen;
}

scRotateControlVertexQtVisual::~scRotateControlVertexQtVisual()
{
}

void scRotateControlVertexQtVisual::MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
	mParentFace->RotateFace(targetMousePos, prevMousePos, angle);
}

void scRotateControlVertexQtVisual::Paint(QPainter& painter)
{
	string fileDir = SC_IMAGE_DIRECTORY;
	fileDir += +"vertex/scRotateControlVertex.png";

	const double width = 60.0;
	const QImage image(QString::fromStdString(fileDir));
	const QRectF imageRect(this->MakeQPointF().x() - width / 2.0, this->MakeQPointF().y() - width / 2.0, width, width);

	painter.drawImage(imageRect, image);
}
