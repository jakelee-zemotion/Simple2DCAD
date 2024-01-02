#include "scMenuBar.h"

using namespace std;

scMenuBar::scMenuBar(QWidget* parent)
	:QMenuBar(parent)
{
	// 1. File
	mFileMenu = make_unique<QMenu>("File");

	mNewSceneAction = make_unique<QAction>("New Scene");
	mOpenSceneAction = make_unique<QAction>("Open Scene");
	mSaveSceneAction = make_unique<QAction>("Save Scene");

	mFileMenu->addAction(mNewSceneAction.get());
	mFileMenu->addAction(mOpenSceneAction.get());
	mFileMenu->addAction(mSaveSceneAction.get());

	// 2. Edit
	mEditMenu = make_unique<QMenu>("Edit");

	// 3. View
	mViewMenu = make_unique<QMenu>("View");
	mObjectListAction = make_unique<QAction>("Object List");
	mViewMenu->addAction(mObjectListAction.get());
	
	this->addMenu(mFileMenu.get());
	this->addMenu(mEditMenu.get());
	this->addMenu(mViewMenu.get());
}

void scMenuBar::ConnectAction(const QObject* mainWindow)
{
	// 1. File
	connect(mNewSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(NewScene()));
	connect(mSaveSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(SaveScene()));
	connect(mOpenSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(LoadScene()));


	// 3. View
	connect(mObjectListAction.get(), SIGNAL(triggered()), mainWindow, SLOT(OpenObjectListDialog()));
}
