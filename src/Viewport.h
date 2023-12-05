#pragma once
#include "ShapeVector.h"

#include <QWidget>


struct ClosedThreshold
{
	int minX, maxX;
	int minY, maxY;
};


class Camera;
class Viewport : public QWidget
{

public:
	Viewport(QWidget* parent = 0);
	~Viewport();

	ShapeVector mShapeObjects;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	bool IsObjectClosed(QPoint start, QPoint end) const;
	bool IsDrawObjectsEmpty() const;

	QVector<QPoint> mShapePoints;
	QVector<QPoint> mTempPoints;
	ClosedThreshold mClosedThreshold;

	QScopedPointer<Camera> mCamera;

	bool mIsDrawing; // Use in mouseReleaseEvent
	bool mIsCtrlPressed;
};

