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
	void SetButtonPressed(std::string name);

private:
	//std::unique_ptr<QToolButton> mDrawButton;
	//std::unique_ptr<QToolButton> mSelectButton;

	std::map<std::string, std::unique_ptr<QToolButton>> mToolButtonMap;
};

