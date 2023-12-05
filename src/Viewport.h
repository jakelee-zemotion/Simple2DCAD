#pragma once
#include "ShapeList.h"
#include "StateMachine.h"

#include <QWidget>


class Camera;
class State;
class Viewport : public QWidget
{

public:
	Viewport(QWidget* parent = 0);
	~Viewport();

	ShapeList mShapeObjects;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	std::unique_ptr<Camera> mCamera;
	std::unique_ptr<State> mState;

	bool mIsCtrlPressed;
};

