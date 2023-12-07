#pragma once

class QPoint;
class QPointF;
class scVertex
{
public:
	scVertex(QPoint& qpoint);
	scVertex(QPointF& qpointF);
	~scVertex();

private:
	double mX;
	double mY;
};

