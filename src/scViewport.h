#pragma once

// qt
#include <QWidget>

// Simple2DCAD
#include "scCamera.h"
#include "scStateMachine.h"

// Forward Declaration
class scScene;
class scCoordinateHelper;
class scGrid;

class scViewport : public QWidget
{
// [Member function section]
public:
	scViewport(QWidget* parent = 0);
	~scViewport();

	void AddState(const std::string& name);
	void TransitState(const std::string& name);

	void ResetScene();
	void OpenScene(const std::string& fileName);
	void SaveScene(const std::string& fileName);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

// [Member variable section]
private:
	const int mViewportWidth;
	const int mViewportHeight;

	std::shared_ptr<scCoordinateHelper> mCoordinateHelper;
	std::shared_ptr<scScene> mScene;
	std::shared_ptr<scGrid> mGrid;

	scCamera mCamera;
	scStateMachine mStateMachine;

	bool mIsCtrlPressed;
};

