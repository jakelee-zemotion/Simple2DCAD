#pragma once
#include <QMainWindow>

class Viewport;
class MenuBar;
class ObjectSelectionToolBar;
class Shape;
class WidgetManager :QObject
{
	Q_OBJECT

public:
	WidgetManager();
	~WidgetManager();

	void SetWidgets(QMainWindow& mainWindow);

private:
	std::unique_ptr<Viewport> mViewport;
	std::unique_ptr<MenuBar> mMenuBar;
	std::unique_ptr<ObjectSelectionToolBar> mObjSelectToolBar;

private slots:
	void OpenObjectListDialog();
	void PressDrawMode();
	void PressSelectMode();
};

