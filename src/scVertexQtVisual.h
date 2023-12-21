#pragma once
#include "scShapeQtVisual.h"

#include <QPointF>

class QPainter;
class scCoordinateHelper;
class scVertexData;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(const QPointF& qpointF, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scVertexQtVisual() override;

	void Move(double targetX, double targetY) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	std::shared_ptr<scVertexData> GetVertexData() const;
	QPointF MakeQPointF();

private:

	std::shared_ptr<scVertexData> mVertexData;
};

