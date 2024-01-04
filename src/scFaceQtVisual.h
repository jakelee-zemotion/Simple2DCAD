#pragma once
#include "scShapeQtVisual.h"
#include "scCommon.h"

#include <list>

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
class scControlVertexQtVisual;
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
	scShapeID GetID() const override;

	void ScaleFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, const scBoxPosition& boxPos, double angle);
	void RotateFace(const scVector2D& targetMousePos, const scVector2D& prevMousePos, double& angle);

	void SetTransformToXY();

	std::list<scShapeID> GetLineStartIDs() const;
	
	scBoundingBox MakeBoundingBox();

private:
	QPolygonF MakeQPolygonF();

	std::shared_ptr<scFaceData> mFaceData;

};

