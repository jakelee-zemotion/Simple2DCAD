#include "scFaceQtVisual.h"

using namespace std;

scFaceQtVisual::scFaceQtVisual(const QRect& viewportSize)
	: scShapeQtVisual(viewportSize)
{
}

scFaceQtVisual::~scFaceQtVisual()
{
}

std::vector<QPointF>& scFaceQtVisual::MakeQPolygonF()
{
	mPolyVertices.clear();

	mPolyVertices.push_back({ 100.0, 100.0 });
	mPolyVertices.push_back({ 100.0, 200.0 });
	mPolyVertices.push_back({ 200.0, 200.0 });
	mPolyVertices.push_back({ 200.0, 100.0 });

	return mPolyVertices;
}

void scFaceQtVisual::MoveShape(double dx, double dy)
{
}

void scFaceQtVisual::Paint(QPainter& painter)
{
	QPen pen(mPenColor);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.drawPolygon(this->MakeQPolygonF().data(), this->MakeQPolygonF().size());
}

bool scFaceQtVisual::HitTest(const QPointF& currMousePos)
{
	return false;
}
