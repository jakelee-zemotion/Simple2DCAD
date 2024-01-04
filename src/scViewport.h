#pragma once

// qt
#include <QWidget>

// Simple2DCAD
#include "scCamera.h"
#include "scStateMachine.h"

class scScene;
class scCoordinateHelper;
class scGrid;
class scViewport : public QWidget
{

public:
	scViewport(QWidget* parent = 0);
	~scViewport();

	void AddState(const std::string& name);
	void TransitState(const std::string& name);

	void ResetScene();
	void OpenScene(std::string fileName);
	void SaveScene(std::string fileName);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	const int mViewportWidth = 700;
	const int mViewportHeight = 500;

	std::shared_ptr<scCoordinateHelper> mCoordinateHelper;
	std::shared_ptr<scScene> mScene;
	std::shared_ptr<scGrid> mGrid;

	scCamera mCamera;
	scStateMachine mStateMachine;

	bool mIsCtrlPressed;
};

