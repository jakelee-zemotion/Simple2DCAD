#pragma once
#include <QMainWindow>

class scViewport;
class scMenuBar;
class scObjectSelectionToolBar;
class scMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	scMainWindow();
	~scMainWindow();

	void SetWidgets();

private:
	std::unique_ptr<scViewport> mViewport;
	std::unique_ptr<scMenuBar> mMenuBar;
	std::unique_ptr<scObjectSelectionToolBar> mObjSelectToolBar;

private slots:
	void OpenObjectListDialog();
	void PressDrawMode(std::string);
};

