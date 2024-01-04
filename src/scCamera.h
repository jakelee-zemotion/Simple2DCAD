#pragma once

// system
#include <memory>

// Simple2DCAD
#include "scMatrixVectorHelper.h"

// Forward Declaration
class QMouseEvent;
class QWheelEvent;
class scScene;

class scCamera
{
// [Member function section]
public:
	scCamera();
	~scCamera();

	void AddPanXY(const scVector2D& currentMousePos);
	void ZoomInOut(const scVector2D& currentMousePos, int mouseDir);

	scVector2D ZoomPan(double x, double y) const;
	scVector2D UnZoomPan(double x, double y) const;

	void SetPrevMousePos(const scVector2D& prevMousePos);

	double GetZoomRatio() const;

// [Member variable section]
private:
	const double mZoomRatio;

	scVector2D mPrevMousePos;

	scMatrix2D mZoomPanMatrix;
	scMatrix2D mInverseZoomPanMatrix;
};