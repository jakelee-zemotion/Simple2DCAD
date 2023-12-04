#pragma once
#include <QVector>
#include <QPoint>

class Shape;
class Camera
{
public:
	Camera();
	~Camera();

	void Pan(QVector<Shape*>& drawObjects, QVector<QPoint>& tempPoints,  QPoint currentMousePos);
	void SetPrevMousePos(QPoint prevMousePos);

private:
	QPoint mPrevMousePos;
};

