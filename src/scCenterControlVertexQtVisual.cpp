#include "scCenterControlVertexQtVisual.h"

using namespace std;

scCenterControlVertexQtVisual::scCenterControlVertexQtVisual(
	scFaceQtVisual* face,
	const scVector2D& pos,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scControlVertexQtVisual(face, pos, coordinateHelper)
{
	mShapeType = SHAPE_TYPE::CENTER_CONTROL_VERTEX;
}

scCenterControlVertexQtVisual::~scCenterControlVertexQtVisual()
{
}

void scCenterControlVertexQtVisual::MoveFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle)
{
}

void scCenterControlVertexQtVisual::Paint(QPainter& painter)
{
	QImage image("C:/Users/Jake/Desktop/code/Simple2DCAD/img/vertex/centerControlVertex.png");
	double width = 20.0;

	QRectF imageRect(this->MakeQPointF().x() - width / 2.0, this->MakeQPointF().y() - width / 2.0, width, width);

	painter.drawImage(imageRect, image);
}
