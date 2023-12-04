#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"
#include "ObjectListDialog.h"


WidgetManager::WidgetManager()
{
	// Init
	mViewport = new Viewport();
	mMenuBar = new MenuBar();
	mObjSelectToolBar = new ObjectSelectionToolBar();

	connect(mMenuBar, SIGNAL(OpenDialogSignal()), this, SLOT(OpenObjectListDialog()));
}

WidgetManager::~WidgetManager()
{
}

void WidgetManager::SetWidgets(QMainWindow& mainWindow)
{
	mainWindow.setCentralWidget(mViewport);
	mainWindow.setMenuBar(mMenuBar);
	mainWindow.addToolBar(Qt::LeftToolBarArea, mObjSelectToolBar);
}

void WidgetManager::OpenObjectListDialog()
{
	ObjectListDialog objectListDialog(mViewport->GetDrawObjects());
	objectListDialog.exec();
}
