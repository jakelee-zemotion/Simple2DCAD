#pragma once
#include "scMatrixVectorHelper.h"

#include <memory>

class QMouseEvent;
class QWheelEvent;
class scScene;
class scCamera
{
public:
	scCamera(std::shared_ptr<scScene> scene);
	~scCamera();

	void AddPanXY(const scVector2D& currentMousePos);
	void ZoomInOut(const scVector2D& currentMousePos, int mouseDir);

	scVector2D ZoomPan(double x, double y) const;
	scVector2D UnZoomPan(double x, double y) const;

	void SetPrevMousePos(const scVector2D& prevMousePos);

private:
	scVector2D mPrevMousePos;

	const double mZoomRatio = 1.2;
	const int mZoomLimitSize = 5;

	scMatrix2D mZoomPanMatrix;
	scMatrix2D mInverseZoomPanMatrix;
};