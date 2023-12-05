#pragma once
#include <QMenuBar>

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget* parent = 0);

	const std::unique_ptr<QAction>& GetObjectListAction() const;

private:
	std::unique_ptr<QMenu> mFileMenu;
	std::unique_ptr<QMenu> mEditMenu;
	std::unique_ptr<QMenu> mViewMenu;

	std::unique_ptr<QAction> mObjectListAction;
};