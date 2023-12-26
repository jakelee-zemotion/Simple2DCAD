#include "scRotateVertexQtVisual.h"

#include "scFaceQtVisual.h"
#include "scCoordinateHelper.h"

#include <qDebug>

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

	QPointF A(0.0, 0.0);
	QPointF B(0.0, 1.0);
	QPointF C(1.0, 0.0);

	QLineF AB(A, B);
	QLineF BC(B, C);
	QLineF CA(C, A);

	double a = BC.length();
	double b = AB.length();
	double c = CA.length();

	qDebug() << a << " " << b << " " << c;

	/*double a = sqrt(QPointF::dotProduct(prevMousePos, targetMousePos));
	double b = sqrt(QPointF::dotProduct(prevMousePos, mCenter));
	double c = sqrt(QPointF::dotProduct(targetMousePos, mCenter));*/

	double angle = acos((b * b + c * c - a * a) / (2.0 * b * c));

	qDebug() << (angle / 3.14) * 360.0;

	mParentFace->RotateFace(angle);
}
