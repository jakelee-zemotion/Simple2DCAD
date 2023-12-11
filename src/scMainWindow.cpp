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

	vector<string> stateName = { "Draw", "Select" };

	for (const auto& name : stateName)
	{
		mViewport->AddState(name);
		mObjSelectToolBar->AddToolButton(name);
	}

	string firstState = stateName[0];
	mViewport->TransitState(firstState);
	mObjSelectToolBar->SetCurrentToolButton(firstState);


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
