#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"
#include "ObjectListDialog.h"


WidgetManager::WidgetManager()
{
	mViewport = new Viewport(mDrawObjects);
	mMenuBar = new MenuBar();
	mObjSelectToolBar = new ObjectSelectionToolBar();

	connect(mMenuBar, SIGNAL(OpenDialogSignal()), this, SLOT(OpenObjectListDialog()));
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

void WidgetManager::OpenObjectListDialog()
{
	ObjectListDialog objectListDialog(mDrawObjects);
	objectListDialog.exec();
}
