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
	mObjSelectToolBar->ConnectToolButton(this);
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
	if (mObjSelectToolBar->SetButtonPressed("Draw"))
	{
		qDebug() << "draw";

		mViewport->TransitState("Draw");
	}
}

void WidgetManager::PressSelectMode()
{
	if (mObjSelectToolBar->SetButtonPressed("Select"))
	{
		qDebug() << "select";
		mViewport->TransitState("Select");
	}

}