#pragma once

// qt
#include <QMainWindow>

// Forward Declaration
class scViewport;
class scMenuBar;
class scToolBar;

class scMainWindow : public QMainWindow
{
	Q_OBJECT

// [Member function section]
public:
	scMainWindow();

	// Since QMainWindow uses Pimpl and scMainWindow has unique_ptr, Destructor must be declared.
	~scMainWindow();

	void SetWidgets();

private slots:
	void TransitState(const std::string& name);
	void NewScene();
	void OpenScene();
	void SaveScene();

// [Member variable section]
private:
	std::unique_ptr<scViewport> mViewport;
	std::unique_ptr<scMenuBar> mMenuBar;
	std::unique_ptr<scToolBar> mToolBar;
};

