#pragma once
#include <QMenuBar>

class scMenuBar : public QMenuBar
{
	Q_OBJECT

public:
	scMenuBar(QWidget* parent = 0);

	void ConnectAction(const QObject* widgetManager);

private:
	std::unique_ptr<QMenu> mFileMenu;
	std::unique_ptr<QMenu> mEditMenu;
	std::unique_ptr<QMenu> mViewMenu;

	std::unique_ptr<QAction> mObjectListAction;
};