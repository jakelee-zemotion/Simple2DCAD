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

	// 1. File
	std::unique_ptr<QAction> mNewAction;
	std::unique_ptr<QAction> mSaveAction;
	std::unique_ptr<QAction> mLoadAction;

	// 3. View
	std::unique_ptr<QAction> mObjectListAction;
};