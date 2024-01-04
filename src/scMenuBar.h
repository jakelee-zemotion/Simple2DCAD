#pragma once

// qt
#include <QMenuBar>

class scMenuBar : public QMenuBar
{
	Q_OBJECT

// [Member function section]
public:
	scMenuBar(QWidget* parent = 0);

	void ConnectAction(const QObject* mainWindow);

// [Memeber variable section]
private:
	std::unique_ptr<QMenu> mFileMenu;
	std::unique_ptr<QMenu> mEditMenu;
	std::unique_ptr<QMenu> mViewMenu;

	// 1. File
	std::unique_ptr<QAction> mNewSceneAction;
	std::unique_ptr<QAction> mOpenSceneAction;
	std::unique_ptr<QAction> mSaveSceneAction;
};