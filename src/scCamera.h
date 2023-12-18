#pragma once

#include <QPoint>

class QMouseEvent;
class QWheelEvent;
class scCamera
{
public:
	scCamera();
	~scCamera();

	void AddPanXY(const QPointF& currentMousePos);
	void MultiplyZoomXY(const QPointF& currentMousePos, int mouseDir);

	//void Pan(const QPointF& currentMousePos);
	//void Zoom(const QPointF& currentMousePos, int mouseDir);
	void SetPrevMousePos(const QPointF& prevMousePos);

	double GetPanX() const;
	double GetPanY() const;

private:
	const double mZoomRatio = 0.2;

	double mPanX;
	double mPanY;

	double mZoomX;
	double mZoomY;

	QPointF mPrevMousePos;
};