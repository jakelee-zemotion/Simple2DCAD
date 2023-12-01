#pragma once
#include <QMenuBar>

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget* parent = 0);

private:
	QMenu* mFileMenu;
	QMenu* mEditMenu;
	QMenu* mViewMenu;

	QAction* mObjectListAction;

private slots:
	void OpenObjectListDialog();
};