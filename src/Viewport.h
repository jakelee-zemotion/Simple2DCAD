#pragma once
#include "ShapeVector.h"

#include <QWidget>


class Camera;
class State;
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
	QScopedPointer<Camera> mCamera;
	QScopedPointer<State> mState;

	bool mIsCtrlPressed;
};

