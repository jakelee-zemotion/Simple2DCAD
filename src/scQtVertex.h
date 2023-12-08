#pragma once
#include "scVertexData.h"
#include "scVertexInterface.h"
#include <QPointF>

class QPoint;
class QPainter;
class scQtVertex : public QPointF, public scVertexInterface
{
public:
	scQtVertex(QPoint& qpoint);
	scQtVertex(QPointF& qpointF);
	~scQtVertex();

	void SetX(double x);
	void SetY(double y);

	double GetX() const;
	double GetY() const;

	void Paint(QPainter& painter);

private:
	scVertexData vertexData;
};

