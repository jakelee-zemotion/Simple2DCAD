#pragma once
#include <QToolBar>

class QVBoxLayout;
class QToolButton;
class scObjectSelectionToolBar : public QToolBar
{
public:
	scObjectSelectionToolBar(QWidget* parent = 0);
	~scObjectSelectionToolBar();

	void ConnectToolButton(QObject* widgetManager);
	bool SetButtonPressed(const std::string name);

private:
	std::map<std::string, std::unique_ptr<QToolButton>> mToolButtonMap;
};

