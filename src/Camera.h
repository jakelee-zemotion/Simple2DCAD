#pragma once
#include "ShapeVector.h"

#include <QVector>
#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class Camera
{
public:
	Camera(ShapeVector& drawObjects, QVector<QPoint>& tempPoints, QPoint viewportSize);
	~Camera();

	void Pan(QPoint currentMousePos);
	void Zoom(QPoint currentMousePos, int mouseDir);
	void SetPrevMousePos(QPoint prevMousePos);

	QPoint ScreenToWorld(QPoint point);
	QPoint WorldToScreen(QPoint point);

private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;

	ShapeVector& mDrawObjects;
	QVector<QPoint>& mTempPoints;
	const QPoint mViewportSize;
};

