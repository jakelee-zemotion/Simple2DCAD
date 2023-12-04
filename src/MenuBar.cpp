#include "MenuBar.h"
#include "ObjectListDialog.h"

MenuBar::MenuBar(QWidget* parent)
	:QMenuBar(parent)
{
	// 1. File
	mFileMenu.reset(new QMenu("File"));

	// 2. Edit
	mEditMenu.reset(new QMenu("Edit"));

	// 3. View
	mViewMenu.reset(new QMenu("View"));
	mObjectListAction.reset(new QAction("Object List"));
	mViewMenu->addAction(mObjectListAction.get());
	
	this->addMenu(mFileMenu.get());
	this->addMenu(mEditMenu.get());
	this->addMenu(mViewMenu.get());
}

const QScopedPointer<QAction>& MenuBar::GetObjectListAction() const
{
	return mObjectListAction;
}