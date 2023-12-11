#include "scObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

using namespace std;

scObjectSelectionToolBar::scObjectSelectionToolBar(QWidget* parent)
	:QToolBar(parent)
{
}

scObjectSelectionToolBar::~scObjectSelectionToolBar()
{
}

void scObjectSelectionToolBar::AddToolButton(std::string name)
{
	mToolButtonMap[name] = make_unique<QToolButton>();
	mToolButtonMap[name]->setText(QString::fromStdString(name));
	mToolButtonMap[name]->setCheckable(true);
	mToolButtonMap[name]->setObjectName(name);
	addWidget(mToolButtonMap[name].get());
}

void scObjectSelectionToolBar::SetCurrentToolButton(std::string name)
{
	mToolButtonMap[name]->setChecked(true);
}

void scObjectSelectionToolBar::ConnectToolButton(QObject* widgetManager)
{
	connect(mToolButtonMap["Draw"].get(), SIGNAL(clicked()), this, SLOT(ClickToolButton()));
	connect(mToolButtonMap["Select"].get(), SIGNAL(clicked()), this, SLOT(ClickToolButton()));

	connect(this, SIGNAL(PressToolButton(std::string)), widgetManager, SLOT(PressDrawMode(std::string)));
}

void scObjectSelectionToolBar::ClickToolButton()
{
	QObject* obj = sender();
	string a = obj->objectName().toStdString();
	emit PressToolButton(obj->objectName().toStdString());
}

bool scObjectSelectionToolBar::SetButtonPressed(const string name)
{
	// If name button is pressed, return false.
	if (!mToolButtonMap[name]->isChecked())
	{
		mToolButtonMap[name]->setChecked(true);
		return false;
	}


	for (const auto& button : mToolButtonMap)
	{
		button.second->setChecked(false);
	}

	mToolButtonMap[name]->setChecked(true);

	return true;
}
