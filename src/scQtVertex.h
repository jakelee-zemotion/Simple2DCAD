#pragma once
#include "scVertexData.h"
#include "scVertexInterface.h"
#include "scQtShapeInterface.h"

#include <QPointF>

class QPainter;
class scQtVertex : public scVertexInterface, public scQtShapeInterface
{
public:
	scQtVertex(QPointF& qpointF);
	~scQtVertex();

	QPointF MakeQPointF();

	void SetX(double x);
	void SetY(double y);

	double GetX() const override;
	double GetY() const override;

	void Paint(QPainter& painter) override;
	void HitTest(QPointF& currMousePos) override;

private:
	scVertexData vertexData;
};

