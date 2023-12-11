#include "scWidgetManager.h"

#include "scViewport.h"
#include "scMenuBar.h"
#include "scObjectSelectionToolBar.h"
#include "scObjectListDialog.h"

#include <QToolButton>

using namespace std;

scWidgetManager::scWidgetManager()
{
	mViewport = make_unique<scViewport>();
	mMenuBar = make_unique<scMenuBar>();
	mObjSelectToolBar = make_unique<scObjectSelectionToolBar>();

	mMenuBar->ConnectAction(this);
	mObjSelectToolBar->ConnectToolButton(this);
}

scWidgetManager::~scWidgetManager()
{
}

void scWidgetManager::SetWidgets(QMainWindow& mainWindow)
{
	mainWindow.setCentralWidget(mViewport.get());
	mainWindow.setMenuBar(mMenuBar.get());
	mainWindow.addToolBar(Qt::BottomToolBarArea, mObjSelectToolBar.get());
}

void scWidgetManager::OpenObjectListDialog()
{
	scObjectListDialog objectListDialog(mViewport->mShapeObjects);
	objectListDialog.exec();
}

void scWidgetManager::PressDrawMode(std::string s)
{
	if (mObjSelectToolBar->SetButtonPressed(s))
	{
		qDebug() << s;

		mViewport->TransitState(s);
	}
}
