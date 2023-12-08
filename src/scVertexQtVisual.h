#pragma once
#include "scVertexData.h"
#include "scVertexVisualInterface.h"
#include "scShapeQtVisualInterface.h"

#include <QPointF>

class QPainter;
class scVertexQtVisual : public scVertexVisualInterface, public scShapeQtVisualInterface
{
public:
	scVertexQtVisual(QPointF& qpointF);
	~scVertexQtVisual();

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

