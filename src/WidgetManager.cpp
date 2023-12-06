#include "WidgetManager.h"

#include "Viewport.h"
#include "MenuBar.h"
#include "ObjectSelectionToolBar.h"
#include "ObjectListDialog.h"

#include <QToolButton>

using namespace std;

WidgetManager::WidgetManager()
{
	mViewport = make_unique<Viewport>();
	mMenuBar = make_unique<MenuBar>();
	mObjSelectToolBar = make_unique<ObjectSelectionToolBar>();

	mMenuBar->ConnectAction(this);
	connect(mObjSelectToolBar->GetDrawButton().get(), SIGNAL(clicked()), this, SLOT(PressDrawMode()));
	connect(mObjSelectToolBar->GetSelectButton().get(), SIGNAL(clicked()), this, SLOT(PressSelectMode()));
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

void WidgetManager::PressDrawMode()
{
	qDebug() << "draw";

	mViewport->setState("Draw");
}

void WidgetManager::PressSelectMode()
{
	qDebug() << "select";

	mViewport->setState("Select");
}