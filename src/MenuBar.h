#pragma once
#include <QMenuBar>

class Shape;
class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QVector<Shape*>& drawObjects, QWidget* parent = 0);

private:
	QMenu* mFileMenu;
	QMenu* mEditMenu;
	QMenu* mViewMenu;

	QAction* mObjectListAction;
	QVector<Shape*>& mDrawObjects;

private slots:
	void OpenObjectListDialog();
};