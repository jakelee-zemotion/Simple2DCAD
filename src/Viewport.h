#pragma once

#include <QWidget>
#include <QVector>


struct ClosedThreshold
{
	int minX, maxX;
	int minY, maxY;
};

struct DrawObject
{
	QVector<QPoint> points;
	bool isPolygon;
};

class Shape;
class Camera;
class Viewport : public QWidget
{

public:
	Viewport(QWidget* parent = 0);
	~Viewport();

	const QVector<Shape*>& GetDrawObjects() const;

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

	QVector<Shape*> mDrawObjects;
	QVector<QPoint> mTempPoints;
	ClosedThreshold mClosedThreshold;

	Camera* mCamera;

	bool mIsDrawing; // Use in mouseReleaseEvent
	Qt::MouseButton mLastPressBtn;
	bool mIsCtrlPressed;
};

