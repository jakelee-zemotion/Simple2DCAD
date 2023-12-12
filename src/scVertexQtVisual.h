#pragma once
#include "scVertexData.h"
#include "scShapeQtVisual.h"

#include <QPointF>

class QPainter;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(QPointF& qpointF);
	~scVertexQtVisual() override;

	QPointF MakeQPointF();

	void SetXY(double x, double y);

	void Paint(QPainter& painter) override;
	bool HitTest(QPointF& currMousePos) override;

	std::shared_ptr<scVertexData> GetVertexData() const;

private:
	std::shared_ptr<scVertexData> mVertexData;
	Qt::GlobalColor mPenColor;
};

