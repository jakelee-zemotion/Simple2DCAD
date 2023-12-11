#pragma once
#include <QToolBar>
#include "scStateName.h"

class QVBoxLayout;
class QToolButton;
class scObjectSelectionToolBar : public QToolBar
{
	Q_OBJECT

public:
	scObjectSelectionToolBar(QWidget* parent = 0);
	~scObjectSelectionToolBar();

	void ConnectToolButton(QObject* widgetManager);
	bool SetButtonPressed(const std::string name);

signals:
	void PressToolButton(std::string name);

private:
	std::map<std::string, std::unique_ptr<QToolButton>> mToolButtonMap;

private slots:
	void ClickToolButton();
};

