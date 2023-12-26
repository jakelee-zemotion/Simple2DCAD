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

	scMatrix2D mZoomPanMatrix;
	scMatrix2D mInverseZoomPanMatrix;
};