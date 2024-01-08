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

	void AddPanXY(const scVector2D& currentMousePos);
	void ZoomInOut(const scVector2D& currentMousePos, int mouseDir);

	scVector2D ZoomPan(const scVector2D& pos) const;
	scVector2D UnZoomPan(const scVector2D& pos) const;

	void SetPrevMousePos(const scVector2D& prevMousePos);

	double GetZoomRatio() const;

// [Member variable section]
private:
	const double mZoomRatio;

	scVector2D mPrevMousePos;

	scMatrix2D mZoomPanMatrix;
	scMatrix2D mInverseZoomPanMatrix;
};