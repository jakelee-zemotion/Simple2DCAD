#pragma once
#include <QToolBar>

class QVBoxLayout;
class QToolButton;
class ObjectSelectionToolBar : public QToolBar
{
public:
	ObjectSelectionToolBar(QWidget* parent = 0);
	~ObjectSelectionToolBar();

	void ConnectToolButton(QObject* widgetManager);
	bool SetButtonPressed(std::string name);

private:
	std::map<std::string, std::unique_ptr<QToolButton>> mToolButtonMap;
};

