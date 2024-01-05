#include "scMenuBar.h"

// Simple2DCAD
#include "scCommon.h"

using namespace std;

scMenuBar::scMenuBar(QWidget* parent)
	:QMenuBar(parent)
{

	string newSceneIconDir = SC_IMAGE_DIRECTORY;
	newSceneIconDir += "icon/toolBar/scNewScene.jpg";
	const QIcon newSceneIcon = QIcon(QString::fromStdString(newSceneIconDir));

	string openSceneIconDir = SC_IMAGE_DIRECTORY;
	openSceneIconDir += "icon/toolBar/scOpenScene.jpg";
	const QIcon openSceneIcon = QIcon(QString::fromStdString(openSceneIconDir));

	string saveSceneIconDir = SC_IMAGE_DIRECTORY;
	saveSceneIconDir += "icon/toolBar/scSaveScene.png";
	const QIcon saveSceneIcon = QIcon(QString::fromStdString(saveSceneIconDir));

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
	
	this->addMenu(mFileMenu.get());
	this->addMenu(mEditMenu.get());
	this->addMenu(mViewMenu.get());
}

scMenuBar::~scMenuBar()
{
}

void scMenuBar::ConnectAction(const QObject* mainWindow)
{
	// 1. File
	connect(mNewSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(NewScene()));
	connect(mOpenSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(OpenScene()));
	connect(mSaveSceneAction.get(), SIGNAL(triggered()), mainWindow, SLOT(SaveScene()));
}
