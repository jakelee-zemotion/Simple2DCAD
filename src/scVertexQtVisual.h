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

	void SetX(double x) override;
	void SetY(double y) override;

	double GetX() const override;
	double GetY() const override;

	void Paint(QPainter& painter) override;
	bool HitTest(QPointF& currMousePos) override;

private:
	scVertexData mVertexData;
	Qt::GlobalColor mPenColor;
};

