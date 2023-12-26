#include "scRotateVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"

#include <qDebug>
#include <QVector3D>

using namespace std;

scRotateVertexQtVisual::scRotateVertexQtVisual(
	const shared_ptr<scFaceQtVisual>& face, 
	const QPointF& point,
	const QPointF& center,
	const shared_ptr<scCoordinateHelper>& coordinateHelper)
		:scVertexQtVisual(SHAPE_TYPE::ROTATE_VERTEX, point, coordinateHelper),
		mParentFace(face), mCenter(center)
{
	mShapeColors[static_cast<int>(COLOR_TYPE::DEFAULT)] = Qt::darkGreen;
}

scRotateVertexQtVisual::~scRotateVertexQtVisual()
{
}

void scRotateVertexQtVisual::Move(const QPointF& targetMousePos, const QPointF& prevMousePos)
{
	scVertexQtVisual::Move(targetMousePos, prevMousePos);

	QPointF A = mCenter;
	QPointF B = prevMousePos;
	QPointF C = targetMousePos;

	QLineF AB(A, B);
	QLineF BC(B, C);
	QLineF CA(C, A);

	double a = BC.length();
	double b = AB.length();
	double c = CA.length();
	
	QVector3D v1(B - A);
	QVector3D v2(C - A);

	QVector3D cross = QVector3D::crossProduct(v1, v2);
	

	/*double a = sqrt(QPointF::dotProduct(prevMousePos, targetMousePos));
	double b = sqrt(QPointF::dotProduct(prevMousePos, mCenter));
	double c = sqrt(QPointF::dotProduct(targetMousePos, mCenter));*/

	double angle = asin(cross.z() / (b * c));

	//qDebug() << (angle / 3.14) * 360.0;

	mParentFace->RotateFace(angle);
}
