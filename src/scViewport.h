#pragma once
#include "scShapeList.h"
#include "scStateMachine.h"

#include <QWidget>


class scCamera;
class scViewport : public QWidget
{

public:
	scViewport(QWidget* parent = 0);
	~scViewport();

	void TransitState(std::string name);

	scShapeList mShapeObjects;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	std::unique_ptr<scCamera> mCamera;
	
	scStateMachine mStateMachine;

	bool mIsCtrlPressed;
};
