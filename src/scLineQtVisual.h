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
		const scCamera& camera, const QRect& viewportSize);
	~scLineQtVisual() override;

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;

	friend class scFaceQtVisual;

private:
	QLineF MakeQLineF();

	std::shared_ptr<scLineData> mLineData;
};

