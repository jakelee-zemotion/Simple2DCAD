#pragma once

class QPoint;
class scVertex
{
public:
	scVertex(QPoint& qpoint);
	~scVertex();

private:
	int x;
	int y;
};

