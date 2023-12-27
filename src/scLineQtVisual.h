#pragma once
#include "scShapeQtVisual.h"

#include <QLineF>

class scCoordinateHelper;
class scLineData;
class scVertexQtVisual;
class scLineQtVisual : public scShapeQtVisual
{
public:
	scLineQtVisual(
		const std::shared_ptr<scVertexQtVisual>& startVertex, 
		const std::shared_ptr<scVertexQtVisual>& endVertex,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scLineQtVisual() override;

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	friend class scFaceQtVisual;

private:
	QLineF MakeQLineF();

	std::shared_ptr<scLineData> mLineData;
};

