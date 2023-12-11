#pragma once
#include "scScene.h"

#include <QPoint>

class QMouseEvent;
class QWheelEvent;

class scCamera
{
public:
	scCamera(scScene& scene, ViewPort* );
	~scCamera();

	void Pan(QPoint currentMousePos);
	void Zoom(QPoint currentMousePos, int mouseDir);
	void SetPrevMousePos(QPoint prevMousePos);

	QPoint ScreenToWorld(currentMousePos, QPoint point);
	QPoint WorldToScreen(QPoint point);

private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;

	scScene& mScene;
	const QPoint mViewportSize;
};

void test_(mouseCurPos, vw, vh, sp)

class ViewPortCotnext(ViewPort, Camera, Scene)
{
	QPoint ScreenToWorld(currentMousePos, QPoint point);
	QPoint WorldToScreen(QPoint point);
};

State(ViewPortCotnext)

