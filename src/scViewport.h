#pragma once
#include "scCamera.h"
#include "scStateMachine.h"

#include <QWidget>

class scScene;
class scCoordinateHelper;
class scViewport : public QWidget
{

public:
	scViewport(QWidget* parent = 0);
	~scViewport();

	void AddState(const std::string& name);
	void TransitState(const std::string& name);

	void ResetScene();
	void SaveScene();
	void LoadScene();

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	std::shared_ptr<scCoordinateHelper> mCoordinateHelper;
	std::shared_ptr<scScene> mScene;

	scCamera mCamera;
	scStateMachine mStateMachine;

	bool mIsCtrlPressed;
};

