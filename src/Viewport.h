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

class Viewport : public QWidget
{

public:
	Viewport(QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
	bool IsObjectClosed(QPoint start, QPoint end) const;
	bool IsDrawObjectsEmpty() const;

	QVector<DrawObject> mDrawObjects;
	ClosedThreshold mClosedThreshold;

	// Use in mouseReleaseEvent
	bool mIsDrawing;
};

