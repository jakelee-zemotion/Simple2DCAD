#pragma once

#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class scCamera
{
public:
	scCamera();
	~scCamera();

	void Pan(const QPoint& currentMousePos);
	void Zoom(const QPoint& currentMousePos, int mouseDir);
	void SetPrevMousePos(const QPoint& prevMousePos);


private:
	const float zoomValue = 1.2f;

	QPoint mPrevMousePos;
};

