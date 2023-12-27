#pragma once
#include "scShapeQtVisual.h"
#include "scMatrixVectorHelper.h"

struct scBoundingBox
{
	scVector2D topLeft;
	scVector2D topRight;
	scVector2D bottomLeft;
	scVector2D bottomRight;

	scVector2D center;
};

class scCoordinateHelper;
class scFaceData;
class scLineData;
class scLineQtVisual;
class scVertexQtVisual;
class scScaleControlVertexQtVisual;
class scRotateControlVertexQtVisual;
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

	void ScaleFace(const QPointF& targetMousePos, const QPointF& prevMousePos);
	void RotateFace(const QPointF& targetMousePos, const QPointF& prevMousePos);

	void ResetControlVertices();
	std::shared_ptr<scRotateControlVertexQtVisual> mRotateControlVertex;
	std::list<std::shared_ptr<scScaleControlVertexQtVisual>> mScaleControlVertexList;

private:
	QPolygonF MakeQPolygonF();
	void ResetBoundingBox();

	std::shared_ptr<scFaceData> mFaceData;

	scBoundingBox mBoundingBox;
};

