#pragma once
#include "scShapeList.h"

#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class scCamera
{
public:
	scCamera(scShapeList& shapeObjects, QPoint viewportSize);
	~scCamera();

	void Pan(QPoint currentMousePos);
	void Zoom(QPoint currentMousePos, int mouseDir);
	void SetPrevMousePos(QPoint prevMousePos);

	QPoint ScreenToWorld(QPoint point);
	QPoint WorldToScreen(QPoint point);

private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;

	scShapeList& mShapeObjects;
	const QPoint mViewportSize;
};
