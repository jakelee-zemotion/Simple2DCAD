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
	Viewport* mViewport;
	MenuBar* mMenuBar;
	ObjectSelectionToolBar* mObjSelectToolBar; 
	
	QVector<Shape*> mDrawObjects;

private slots:
	void OpenObjectListDialog();
};

