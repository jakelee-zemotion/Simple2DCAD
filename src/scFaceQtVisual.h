#pragma once

// system
#include <list>

// Simple2DCAD
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

// Forward Declaration
class scCoordinateHelper;
class scFaceData;
class scLineData;
class scLineQtVisual;
class scVertexQtVisual;
class scControlVertexQtVisual;

class scFaceQtVisual : public scShapeQtVisual
{
// [Member function section]
public:
	scFaceQtVisual(const std::list<std::shared_ptr<scLineQtVisual>>& lineList, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;
	scShapeID GetID() const override;

	void ScaleFace(const scVector2D& scale, const scVector2D& trans, const double angle);
	void RotateFace(const scVector2D& trans, const double angle);

	scBoundingBox MakeBoundingBox();

	void SetTransformToXY();

	std::list<scShapeID> GetLineStartIDs() const;

private:
	QPolygonF MakeQPolygonF();

// [Member variable section]
private:
	std::shared_ptr<scFaceData> mFaceData;

};

