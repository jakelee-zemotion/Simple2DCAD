#pragma once

// qt
#include <QToolBar>

// Forward Declaration
class QVBoxLayout;
class QToolButton;

class scToolBar : public QToolBar
{
	Q_OBJECT

// [Member function section]
public:
	scToolBar(QWidget* parent = 0);
	~scToolBar();

	void AddEditToolButton(const std::string& name);
	void SetCurrentToolButton(const std::string& name);

	void ConnectToolButton(const std::string& name);
	void ConnectTransitSignal(const QObject* widgetManager);
	bool SetButtonPressed(const std::string& name);

signals:
	void PressToolButton(const std::string& name);

private slots:
	void ClickToolButton();

// [Memeber variable section]
private:
	std::unique_ptr<QToolButton> mNewSceneToolButton;
	std::unique_ptr<QToolButton> mOpenSceneToolButton;
	std::unique_ptr<QToolButton> mSaveSceneToolButton;

	std::map<std::string, std::unique_ptr<QToolButton>> mEditToolButtonMap;
};

