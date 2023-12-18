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
	
	// Connect signals/slots
	mMenuBar->ConnectAction(this);
	mObjSelectToolBar->ConnectTransitSignal(this);

	// Add states and toolButtons.
	vector<string> stateName = { "Draw", "SelectAll", "SelectVertex", "SelectLine", "SelectFace" };

	for (const auto& name : stateName)
	{
		mViewport->AddState(name);
		mObjSelectToolBar->AddToolButton(name);
		mObjSelectToolBar->ConnectToolButton(name);
	}

	string firstState = stateName[0];
	mViewport->TransitState(firstState);
	mObjSelectToolBar->SetCurrentToolButton(firstState);


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
	//scObjectListDialog objectListDialog(mViewport->mScene);
	//objectListDialog.exec();
}

void scMainWindow::TransitState(const string& name)
{
	if (mObjSelectToolBar->SetButtonPressed(name))
	{
		qDebug() << name;

		mViewport->TransitState(name);
	}
}
