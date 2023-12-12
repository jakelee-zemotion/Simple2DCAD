#pragma once
#include "scScene.h"
#include "scCamera.h"
#include "scStateMachine.h"

#include <QWidget>

class scViewport : public QWidget
{

public:
	scViewport(QWidget* parent = 0);
	~scViewport();

	void AddState(const std::string& name);
	void TransitState(const std::string& name);


protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	scCamera mCamera;
	std::shared_ptr<scScene> mScene;
	
	scStateMachine mStateMachine;

	bool mIsCtrlPressed;
};

