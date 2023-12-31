#include "scMainWindow.h"

// qt
#include <QToolButton>
#include <QFileDialog>

// Simple2DCAD
#include "scViewport.h"
#include "scMenuBar.h"
#include "scToolBar.h"
#include "scCommon.h"

using namespace std;

scMainWindow::scMainWindow()
{
	mViewport = make_unique<scViewport>();
	mMenuBar = make_unique<scMenuBar>();
	mToolBar = make_unique<scToolBar>(this);
	
	// Connect signals/slots
	mMenuBar->ConnectAction(this);
	mToolBar->ConnectTransitSignal(this);

	// Add states and toolButtons.
	const vector<string> stateName = 
	{ 
		SC_DRAW_LINE,
		SC_SELECT_ALL,
		SC_SELECT_VERTEX,
		SC_SELECT_LINE,
		SC_SELECT_FACE
	};

	for (const auto& name : stateName)
	{
		mViewport->AddState(name);
		mToolBar->AddEditToolButton(name);
		mToolBar->ConnectToolButton(name);
	}

	const string firstState = stateName[0];
	mViewport->TransitState(firstState);
	mToolBar->SetCurrentToolButton(firstState);


}

scMainWindow::~scMainWindow()
{
}

void scMainWindow::SetWidgets()
{
	this->setCentralWidget(mViewport.get());
	this->setMenuBar(mMenuBar.get());
	this->addToolBar(Qt::TopToolBarArea, mToolBar.get());
}

void scMainWindow::TransitState(const string& name)
{
	if (mToolBar->SetButtonPressed(name))
	{
		mViewport->TransitState(name);
	}
}

void scMainWindow::NewScene()
{
	mViewport->ResetScene();
}

void scMainWindow::OpenScene()
{
	const QString fileName = QFileDialog::getOpenFileName(this, "Load Scene", "", "JSON (*.json)");
	mViewport->OpenScene(fileName.toStdString());
}

void scMainWindow::SaveScene()
{
	const QString fileName = QFileDialog::getOpenFileName(this, "Save Scene", "", "JSON (*.json)");
	mViewport->SaveScene(fileName.toStdString());
}
