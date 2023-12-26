#pragma once
#include "scMatrixVectorHelper.h"

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
	void ZoomInOut(const QPointF& currentMousePos, int mouseDir);

	scVector2D ZoomPan(double x, double y) const;
	scVector2D UnZoomPan(double x, double y) const;

	void SetPrevMousePos(const QPointF& prevMousePos);

private:
	QPointF mPrevMousePos;

	const double mZoomRatio = 1.2;
	const int mZoomLimitSize = 5;
	const int mPanLimitSize = mZoomLimitSize + 1;
	enum class ZOOM { IN, OUT };

	ZOOM mPrevZoomState;
	int mZoomBackIdx;
	int mPanBackIdx;
	std::vector<std::pair<double, double>> mZoomCenterVector;
	std::vector<std::pair<double, double>> mPanDistVector;

	scMatrix2D mZoomPanMatrix;

	void AddRemoveZoomPanVectorElement(const QPointF& currentMousePos, const ZOOM& currZoomState);
};