#pragma once
#include "scShapeQtVisual.h"

#include <QPointF>

class QPainter;
class scCoordinateHelper;
class scVertexData;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(const QPointF& point, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	virtual ~scVertexQtVisual() override;

	virtual void Move(const QPointF& targetMousePos, const QPointF& prevMousePos = QPoint(0.0, 0.0)) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	std::shared_ptr<scVertexData> GetVertexData() const;
	QPointF MakeQPointF();

protected:
	scVertexQtVisual(
		const SHAPE_TYPE shapeType,
		const QPointF& point, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	void Initialize(const QPointF& point);

	std::shared_ptr<scVertexData> mVertexData;
};

