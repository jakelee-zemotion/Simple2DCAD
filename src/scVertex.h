#pragma once

class QPoint;
class QPointF;
class scVertex
{
public:
	scVertex(QPoint& qpoint);
	scVertex(QPointF& qpointF);
	~scVertex();

	double GetX() const;
	double GetY() const;

private:
	double mX;
	double mY;
};

