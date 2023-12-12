#pragma once
#include "scScene.h"

#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class scCamera
{
public:
	scCamera();
	~scCamera();

	void Pan(QPoint currentMousePos);
	void Zoom(QPoint currentMousePos, int mouseDir);
	void SetPrevMousePos(QPoint prevMousePos);


private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;
};

