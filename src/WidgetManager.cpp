#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"
#include "ObjectListDialog.h"


WidgetManager::WidgetManager()
{
	mViewport.reset(new Viewport());
	mMenuBar.reset(new MenuBar());
	mObjSelectToolBar.reset(new ObjectSelectionToolBar());

	connect(mMenuBar->GetObjectListAction().get(), SIGNAL(triggered()), this, SLOT(OpenObjectListDialog()));
}

WidgetManager::~WidgetManager()
{
}

void WidgetManager::SetWidgets(QMainWindow& mainWindow)
{
	mainWindow.setCentralWidget(mViewport.get());
	mainWindow.setMenuBar(mMenuBar.get());
	mainWindow.addToolBar(Qt::BottomToolBarArea, mObjSelectToolBar.get());
}

void WidgetManager::OpenObjectListDialog()
{
	ObjectListDialog objectListDialog(mViewport->mDrawObjects);
	objectListDialog.exec();
}
