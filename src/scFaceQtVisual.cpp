#include "scFaceQtVisual.h"

scFaceQtVisual::scFaceQtVisual(const QRect& viewportSize)
	: scShapeQtVisual(viewportSize)
{
}

scFaceQtVisual::~scFaceQtVisual()
{
}

void scFaceQtVisual::MoveShape(double dx, double dy)
{
}

void scFaceQtVisual::Paint(QPainter& painter)
{
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	return false;
}
