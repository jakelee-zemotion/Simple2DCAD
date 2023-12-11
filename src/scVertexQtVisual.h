#pragma once
#include "scVertexData.h"
#include "scShapeQtVisualInterface.h"

#include <QPointF>

class QPainter;
class scVertexQtVisual : public scShapeQtVisualInterface
{
public:
	scVertexQtVisual(QPointF& qpointF);
	~scVertexQtVisual() override;

	QPointF MakeQPointF();

	void SetX(double x);
	void SetY(double y);

	double GetX() const;
	double GetY() const;

	void Paint(QPainter& painter) override;
	bool HitTest(QPointF& currMousePos) override;

	std::shared_ptr<scVertexData> GetVertexData() const;

private:
	std::shared_ptr<scVertexData> mVertexData;
	Qt::GlobalColor mPenColor;
};

