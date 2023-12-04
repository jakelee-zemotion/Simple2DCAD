#pragma once
#include <QVector>
#include <QPoint>

class Shape;
class QMouseEvent;
class QWheelEvent;
class Camera
{
public:
	Camera(QVector<Shape*>& drawObjects, QVector<QPoint>& tempPoints, QPoint viewportSize);
	~Camera();

	void Pan(QPoint currentMousePos);
	void Zoom(QWheelEvent* event, bool isCtrlPressed, QPoint currentMousePos);
	void SetPrevMousePos(QPoint prevMousePos);

	QPoint ScreenToWorld(QPoint point);
	QPoint WorldToScreen(QPoint point);

private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;

	QVector<Shape*>& mDrawObjects;
	QVector<QPoint>& mTempPoints;
	const QPoint mViewportSize;
};

