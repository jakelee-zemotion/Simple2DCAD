#include "scMainWindow.h"

#include "scViewport.h"
#include "scMenuBar.h"
#include "scObjectSelectionToolBar.h"
#include "scObjectListDialog.h"

#include <QToolButton>

using namespace std;

scMainWindow::scMainWindow()
{
	mViewport = make_unique<scViewport>();
	mMenuBar = make_unique<scMenuBar>();
	mObjSelectToolBar = make_unique<scObjectSelectionToolBar>();


	mViewport->AddState("Draw");
	mObjSelectToolBar->AddToolButton("Draw");
	mViewport->AddState("Select");
	mObjSelectToolBar->AddToolButton("Select");

	mViewport->TransitState("Draw");
	mObjSelectToolBar->SetCurrentToolButton("Draw");


	mMenuBar->ConnectAction(this);
	mObjSelectToolBar->ConnectToolButton(this);

}

scMainWindow::~scMainWindow()
{
}

void scMainWindow::SetWidgets()
{
	this->setCentralWidget(mViewport.get());
	this->setMenuBar(mMenuBar.get());
	this->addToolBar(Qt::BottomToolBarArea, mObjSelectToolBar.get());
}

void scMainWindow::OpenObjectListDialog()
{
	scObjectListDialog objectListDialog(mViewport->mShapeObjects);
	objectListDialog.exec();
}

void scMainWindow::PressDrawMode(std::string s)
{
	if (mObjSelectToolBar->SetButtonPressed(s))
	{
		qDebug() << s;

		mViewport->TransitState(s);
	}
}
