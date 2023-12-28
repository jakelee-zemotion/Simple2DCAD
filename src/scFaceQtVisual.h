#pragma once
#include "scShapeQtVisual.h"
#include "scCommon.h"

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

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;

	void ScaleFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, const BOX_POSITION& boxPos);
	void RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos);

	void ResetControlVertices();
	std::shared_ptr<scRotateControlVertexQtVisual> mRotateControlVertex;
	std::vector<std::shared_ptr<scScaleControlVertexQtVisual>> mScaleControlVertexVector;

private:
	QPolygonF MakeQPolygonF();
	void ResetBoundingBox();

	std::shared_ptr<scFaceData> mFaceData;

	scBoundingBox mBoundingBox;
};

