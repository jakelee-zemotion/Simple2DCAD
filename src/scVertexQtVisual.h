#pragma once
#include "scShapeQtVisual.h"

class scVertexData;
class scVertexQtVisual : public scShapeQtVisual
{
public:
	scVertexQtVisual(const scVector2D& pos, const scCamera& camera, const QRect& viewportSize);
	virtual ~scVertexQtVisual() override;

	virtual void Move(const scVector2D& targetMousePos, const scVector2D& prevMousePos = scVector2D(0.0, 0.0)) override;
	void Paint(QPainter& painter) override;
	bool HitTest(const scVector2D& currMousePos) override;

	void SetXY(const scVector2D& pos);
	scVector2D GetXY() const;

	friend class scLineQtVisual;

	std::shared_ptr<scVertexData> mVertexData;
protected:
	QPointF MakeQPointF() const;

};

