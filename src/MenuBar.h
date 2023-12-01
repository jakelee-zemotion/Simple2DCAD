#pragma once
#include <QMenuBar>

class MenuBar : public QMenuBar
{
public:
	MenuBar(QWidget* parent = 0);

private:
	QMenu* mFileMenu;
	QMenu* mEditMenu;
	QMenu* mViewMenu;

	QAction* mObjectListAction;
};