#include "scMainWindow.h"

#include "scViewport.h"
#include "scMenuBar.h"
#include "scToolBar.h"
#include "scCommon.h"

#include <QToolButton>
#include <QFileDialog>

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
		mToolBar->AddEditToolButton(name);
		mToolBar->ConnectToolButton(name);
	}

	string firstState = stateName[0];
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
		qDebug() << name;

		mViewport->TransitState(name);
	}
}

void scMainWindow::NewScene()
{
	mViewport->ResetScene();
}

void scMainWindow::OpenScene()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Load Scene", "", "JSON (*.json)");
	mViewport->OpenScene(fileName.toStdString());
}

void scMainWindow::SaveScene()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Save Scene", "", "JSON (*.json)");
	mViewport->SaveScene(fileName.toStdString());
}
