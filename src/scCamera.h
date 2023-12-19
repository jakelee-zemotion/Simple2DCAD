#pragma once

#include <QPoint>
#include <list>
#include <vector>


class QMouseEvent;
class QWheelEvent;
class scCamera
{
public:
	scCamera();
	~scCamera();

	void AddPanXY(const QPointF& currentMousePos);
	void MultiplyDivideZoomXY(const QPointF& currentMousePos, int mouseDir);

	std::pair<double, double> Pan(double x, double y) const;
	std::pair<double, double> UnPan(double x, double y) const;
	std::pair<double, double> Zoom(double x, double y) const;
	std::pair<double, double> UnZoom(double x, double y) const;

	void SetPrevMousePos(const QPointF& prevMousePos);

private:
	QPointF mPrevMousePos;

	// Pan
	double mPanX;
	double mPanY;

	// Zoom
	const double mZoomRatio = 1.2;
	const size_t mZoomLimit = 5;
	enum class ZOOM { IN, OUT };

	std::vector<std::pair<double, double>> mZoomCenterVector;
	ZOOM mZoomState;
};