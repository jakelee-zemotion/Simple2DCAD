#pragma once
#include <QMainWindow>

class scViewport;
class scMenuBar;
class scObjectSelectionToolBar;
class scWidgetManager : public QObject
{
	Q_OBJECT

public:
	scWidgetManager();
	~scWidgetManager();

	void SetWidgets(QMainWindow& mainWindow);

private:
	std::unique_ptr<scViewport> mViewport;
	std::unique_ptr<scMenuBar> mMenuBar;
	std::unique_ptr<scObjectSelectionToolBar> mObjSelectToolBar;

private slots:
	void OpenObjectListDialog();
	void PressDrawMode();
	void PressSelectMode();
};

