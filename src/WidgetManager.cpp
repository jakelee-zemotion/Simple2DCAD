#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"


WidgetManager::WidgetManager()
{
	mViewport = new Viewport(mDrawObjects);
	mMenuBar = new MenuBar();
	mObjSelectToolBar = new ObjectSelectionToolBar();
}

WidgetManager::~WidgetManager()
{
	for (const auto& object : mDrawObjects)
	{
		delete object;
	}
}

void WidgetManager::SetWidgets(QMainWindow& mainWindow)
{
	mainWindow.setCentralWidget(mViewport);
	mainWindow.setMenuBar(mMenuBar);
	mainWindow.addToolBar(Qt::LeftToolBarArea, mObjSelectToolBar);
}

