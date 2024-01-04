#pragma once

// qt
#include <QLineF>

// Simple2DCAD
#include "scShapeQtVisual.h"

// Forward Declaration
class scCoordinateHelper;
class scLineData;
class scVertexQtVisual;

class scLineQtVisual : public scShapeQtVisual
{
// [Member function section]
public:
	scLineQtVisual(const std::shared_ptr<scVertexQtVisual>& startVertex, const std::shared_ptr<scVertexQtVisual>& endVertex, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	~scLineQtVisual() override;

	void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;
	scShapeID GetID() const override;

	scShapeID GetStartVertexID();
	scShapeID GetEndVertexID();

private:
	QLineF MakeQLineF();

// [Member variable section]
public:
	friend class scFaceQtVisual;

private:
	std::shared_ptr<scLineData> mLineData;
};

