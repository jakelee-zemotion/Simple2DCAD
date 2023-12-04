#pragma once
#include <QMenuBar>

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget* parent = 0);

	const QScopedPointer<QAction>& GetObjectListAction() const;

private:
	QScopedPointer<QMenu> mFileMenu;
	QScopedPointer<QMenu> mEditMenu;
	QScopedPointer<QMenu> mViewMenu;

	QScopedPointer<QAction> mObjectListAction;
};