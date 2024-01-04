#pragma once
#include <QMenuBar>

class scMenuBar : public QMenuBar
{
	Q_OBJECT

public:
	scMenuBar(QWidget* parent = 0);

	void ConnectAction(const QObject* mainWindow);

private:
	std::unique_ptr<QMenu> mFileMenu;
	std::unique_ptr<QMenu> mEditMenu;
	std::unique_ptr<QMenu> mViewMenu;

	// 1. File
	std::unique_ptr<QAction> mNewSceneAction;
	std::unique_ptr<QAction> mOpenSceneAction;
	std::unique_ptr<QAction> mSaveSceneAction;
};