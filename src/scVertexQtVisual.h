#pragma once
#include "scVertexData.h"
#include "scShapeQtVisual.h"

#include <QPointF>

class QPainter;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(const QPointF& qpointF, const QRect& viewportSize);
	~scVertexQtVisual() override;

	QPointF MakeQPointF();

	void MoveShape(double dx, double dy) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;
	void SetShapeColor(const Qt::GlobalColor& color) override;

	std::shared_ptr<scVertexData> GetVertexData() const;

private:
	std::shared_ptr<scVertexData> mVertexData;
};

