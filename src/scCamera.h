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

	std::pair<double, double> Zoom(double x, double y) const;
	std::pair<double, double> UnZoom(double x, double y) const;

	void SetPrevMousePos(const QPointF& prevMousePos);

private:
	QPointF mPrevMousePos;

	const double mZoomRatio = 1.2;
	const int mZoomLimitSize = 5;
	const int mPanLimitSize = mZoomLimitSize + 1;
	enum class ZOOM { IN, OUT };

	ZOOM mZoomState;
	int mZoomBackIdx;
	int mPanBackIdx;
	std::vector<std::pair<double, double>> mZoomCenterVector;
	std::vector<std::pair<double, double>> mPanDistVector;

	void PushPopZoomCenterVector(const QPointF& currentMousePos, const ZOOM& currZoomState);
};