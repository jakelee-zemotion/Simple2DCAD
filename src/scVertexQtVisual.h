#pragma once
#include "scVertexData.h"
#include "scShapeQtVisual.h"

#include <QPointF>

class QPainter;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(SHAPE_TYPE shapeType, const QPointF& qpointF, const QRect& viewportSize);
	~scVertexQtVisual() override;

	void Move(double x, double y) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	std::shared_ptr<scVertexData> GetVertexData() const;
	QPointF MakeQPointF();

private:

	std::shared_ptr<scVertexData> mVertexData;
};

