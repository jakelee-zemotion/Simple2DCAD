#pragma once

#include <QPoint>
#include <list>


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
	struct ZoomData
	{
		double centerX;
		double centerY;
		int mouseDir;
	};

	const double mZoomRatio = 1.2;

	double mPanX;
	double mPanY;

	std::list<ZoomData> mZoomDataList;

	//std::vector

	QPointF mPrevMousePos;
};