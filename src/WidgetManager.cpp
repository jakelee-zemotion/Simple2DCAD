#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"
#include "ObjectListDialog.h"

using namespace std;

WidgetManager::WidgetManager()
{
	mViewport = make_unique<Viewport>();
	mMenuBar = make_unique<MenuBar>();
	mObjSelectToolBar = make_unique<ObjectSelectionToolBar>();

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
	ObjectListDialog objectListDialog(mViewport->mShapeObjects);
	objectListDialog.exec();
}
