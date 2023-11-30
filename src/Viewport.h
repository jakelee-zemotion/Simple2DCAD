#pragma once
#include <QWidget>
#include <QVector>



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
	QVector<QVector<QPoint>> mPolylineVector;

	// Use in mouseReleaseEvent
	bool mIsDrawing;
};

