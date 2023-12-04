#pragma once
#include <QVector>
#include <QPoint>

class Shape;
class Camera
{
public:
	Camera();
	~Camera();

	void Pan(QVector<Shape*> drawObjects, QPoint currentMousePos);

private:

};

