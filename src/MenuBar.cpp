#include "MenuBar.h"
#include "ObjectListDialog.h"

MenuBar::MenuBar(QVector<Shape*>& drawObjects, QWidget* parent)
	:QMenuBar(parent), mDrawObjects(drawObjects)
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
	ObjectListDialog objectListDialog(mDrawObjects);
	objectListDialog.exec();
}