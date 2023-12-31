#include "scCenterControlVertexQtVisual.h"

using namespace std;

scCenterControlVertexQtVisual::scCenterControlVertexQtVisual(const std::shared_ptr<scFaceQtVisual> face, const scVector2D& pos, const shared_ptr<scCoordinateHelper>& coordinateHelper)
	:scControlVertexQtVisual(face, pos, coordinateHelper)
{
	mShapeType = scShapeType::CENTER_CONTROL_VERTEX;
}

void scCenterControlVertexQtVisual::Paint(QPainter& painter)
{
	string fileDir = SC_IMAGE_DIRECTORY;
	fileDir += "vertex/scCenterControlVertex.png";

	const double width = 20.0;
	const QImage image(QString::fromStdString(fileDir));
	const QRectF imageRect(this->MakeQPointF().x() - width / 2.0, this->MakeQPointF().y() - width / 2.0, width, width);

	painter.drawImage(imageRect, image);
}
