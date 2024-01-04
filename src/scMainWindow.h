#pragma once
#include <QMainWindow>

class scViewport;
class scMenuBar;
class scToolBar;
class scMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	scMainWindow();
	~scMainWindow();

	void SetWidgets();

private:
	std::unique_ptr<scViewport> mViewport;
	std::unique_ptr<scMenuBar> mMenuBar;
	std::unique_ptr<scToolBar> mToolBar;

private slots:
	void TransitState(const std::string& name);
	void NewScene();
	void OpenScene();
	void SaveScene();
};

