#pragma once
#include <QToolBar>

class QVBoxLayout;
class QToolButton;
class scObjectSelectionToolBar : public QToolBar
{
	Q_OBJECT

public:
	scObjectSelectionToolBar(QWidget* parent = 0);
	~scObjectSelectionToolBar();

	void AddToolButton(const std::string& name);
	void SetCurrentToolButton(const std::string& name);

	void ConnectToolButton(const std::string& name);
	void ConnectTransitSignal(const QObject* widgetManager);
	bool SetButtonPressed(const std::string& name);

signals:
	void PressToolButton(const std::string& name);

private:
	std::unique_ptr<QToolButton> mNewSceneToolButton;

	std::map<std::string, std::unique_ptr<QToolButton>> mToolButtonMap;

private slots:
	void ClickToolButton();
};

