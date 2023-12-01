#include "MenuBar.h"
#include "ObjectListDialog.h"

MenuBar::MenuBar(QWidget* parent)
	:QMenuBar(parent)
{
	// 1. File
	mFileMenu = new QMenu("File");

	// 2. Edit
	mEditMenu = new QMenu("Edit");

	// 3. View
	mViewMenu = new QMenu("View");
	mObjectListAction = new QAction("Object List");
	mViewMenu->addAction(mObjectListAction);
	connect(mObjectListAction, SIGNAL(triggered()), this, SLOT(OpenObjectListDialog()));

	this->addMenu(mFileMenu);
	this->addMenu(mEditMenu);
	this->addMenu(mViewMenu);
}

void MenuBar::OpenObjectListDialog()
{
	ObjectListDialog objectListDialog;
	objectListDialog.exec();
}