#pragma once
#include "scShapeQtVisual.h"
#include "scScaleControlVertexQtVisual.h"
#include "scRotateControlVertexQtVisual.h"

struct scBoundingBox
{
	QPointF topLeft;
	QPointF topRight;
	QPointF bottomLeft;
	QPointF bottomRight;

	QPointF center;
};

class scCoordinateHelper;
class scFaceData;
class scLineData;
class scLineQtVisual;
class scFaceQtVisual : public scShapeQtVisual
{
public:
	scFaceQtVisual(
		const std::list<std::shared_ptr<scLineQtVisual>>& lineList,
		const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scFaceQtVisual() override;

	void Move(const QPointF& targetMousePos, const QPointF& prevMousePos) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const QPointF& currMousePos) override;

	void ScaleFace(double dx, double dy, double transX, double transY);
	void RotateFace(double sinX, double cosX, double transX, double transY);

	scBoundingBox GetBoundingBox();

private:
	QPolygonF MakeQPolygonF();

	std::shared_ptr<scFaceData> mFaceData;

	//scRotateControlVertexQtVisual mRotateControlVertex;
};

