#pragma once
#include "ShapeList.h"

#include <QVector>
#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class Camera
{
public:
	Camera(ShapeList& shapeObjects, QPoint viewportSize);
	~Camera();

	void Pan(QPoint currentMousePos);
	void Zoom(QPoint currentMousePos, int mouseDir);
	void SetPrevMousePos(QPoint prevMousePos);

	QPoint ScreenToWorld(QPoint point);
	QPoint WorldToScreen(QPoint point);

private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;

	ShapeList& mShapeObjects;
	const QPoint mViewportSize;
};

