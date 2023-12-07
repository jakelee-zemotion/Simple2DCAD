#pragma once

class QPoint;
class scPoint
{
public:
	scPoint(QPoint& qpoint);
	~scPoint();

private:
	int x;
	int y;
};

