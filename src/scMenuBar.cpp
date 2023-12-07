#include "scMenuBar.h"

using namespace std;

scMenuBar::scMenuBar(QWidget* parent)
	:QMenuBar(parent)
{
	// 1. File
	mFileMenu = make_unique<QMenu>("File");

	// 2. Edit
	mEditMenu = make_unique<QMenu>("Edit");

	// 3. View
	mViewMenu = make_unique<QMenu>("View");
	mObjectListAction.reset(new QAction("Object List"));
	mViewMenu->addAction(mObjectListAction.get());
	
	this->addMenu(mFileMenu.get());
	this->addMenu(mEditMenu.get());
	this->addMenu(mViewMenu.get());
}

void scMenuBar::ConnectAction(const QObject* widgetManager)
{
	connect(mObjectListAction.get(), SIGNAL(triggered()), widgetManager, SLOT(OpenObjectListDialog()));
}
