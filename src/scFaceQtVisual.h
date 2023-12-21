#pragma once
#include "scShapeQtVisual.h"

struct scBoundingBox
{
	QPointF topLeft;
	QPointF topRight;
	QPointF bottomLeft;
	QPointF bottomRight;
};

class scCoordinateHelper;
class scFaceData;
class scLineData;
class scFaceQtVisual : public scShapeQtVisual
{
public:
	scFaceQtVisual(
		const std::list<std::shared_ptr<scLineData>>& lineList, 
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scFaceQtVisual() override;

	void Move(double dx, double dy) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	void ScaleFace(double dx, double dy);
	void RotateFace(double theta);

	scBoundingBox GetBoundingBox();

private:
	QPolygonF MakeQPolygonF();

	std::shared_ptr<scFaceData> mFaceData;
};

