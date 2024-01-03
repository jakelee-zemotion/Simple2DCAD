#include "scMainWindow.h"

#include "scViewport.h"
#include "scMenuBar.h"
#include "scObjectSelectionToolBar.h"
#include "scObjectListDialog.h"
#include "scCommon.h"

#include <QToolButton>
#include <QFileDialog>

using namespace std;

scMainWindow::scMainWindow()
{
	mViewport = make_unique<scViewport>();
	mMenuBar = make_unique<scMenuBar>();
	mObjSelectToolBar = make_unique<scObjectSelectionToolBar>(this);
	
	// Connect signals/slots
	mMenuBar->ConnectAction(this);
	mObjSelectToolBar->ConnectTransitSignal(this);

	// Add states and toolButtons.
	vector<string> stateName = 
	{ 
		DRAW_LINE,
		SELECT_ALL,
		SELECT_VERTEX,
		SELECT_LINE,
		SELECT_FACE
	};

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
	this->addToolBar(Qt::TopToolBarArea, mObjSelectToolBar.get());

	//QString fileName = QFileDialog::getOpenFileName(this, "Save Scene", "", "JSON (*.json)");
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

void scMainWindow::NewScene()
{
	mViewport->ResetScene();
}

void scMainWindow::SaveScene()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Save Scene", "", "JSON (*.json)");
	mViewport->SaveScene(fileName.toStdString());
}

void scMainWindow::LoadScene()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Load Scene", "", "JSON (*.json)");
	mViewport->LoadScene(fileName.toStdString());
}
