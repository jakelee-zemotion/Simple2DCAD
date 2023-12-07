#pragma once
#include <QVector>
#include <QPoint>
#include <QPainter>

class scShape
{
public:
	scShape(std::vector<QPoint>& points);
	~scShape();

	virtual void Paint(QPainter& painter) = 0;

//protected:
	std::vector<QPoint> mPoints;
	QString name;

	static int nameCnt;
};

