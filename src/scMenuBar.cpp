#include "scMenuBar.h"

using namespace std;

scMenuBar::scMenuBar(QWidget* parent)
	:QMenuBar(parent)
{

	string newSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/NewScene.jpg";
	QIcon newSceneIcon = QIcon(QString::fromStdString(newSceneIconDir));

	string openSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/OpenScene.jpg";
	QIcon openSceneIcon = QIcon(QString::fromStdString(openSceneIconDir));

	string saveSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/SaveScene.png";
	QIcon saveSceneIcon = QIcon(QString::fromStdString(saveSceneIconDir));

	// 1. File
	mFileMenu = make_unique<QMenu>("File");

	mNewSceneAction = make_unique<QAction>("New Scene");
	mNewSceneAction->setIcon(newSceneIcon);
	mOpenSceneAction = make_unique<QAction>("Open Scene");
	mOpenSceneAction->setIcon(openSceneIcon);
	mSaveSceneAction = make_unique<QAction>("Save Scene");
	mSaveSceneAction->setIcon(saveSceneIcon);

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
	connect(mOpenSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(OpenScene()));
	connect(mSaveSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(SaveScene()));


	// 3. View
	connect(mObjectListAction.get(), SIGNAL(triggered()), mainWindow, SLOT(OpenObjectListDialog()));
}
