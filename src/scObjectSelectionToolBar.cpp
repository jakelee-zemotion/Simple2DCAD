#include "scObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

using namespace std;

scObjectSelectionToolBar::scObjectSelectionToolBar(QWidget* parent)
	:QToolBar(parent)
{
	mToolButtonMap["Draw"] = make_unique<QToolButton>();
	mToolButtonMap["Draw"]->setText("Draw");
	mToolButtonMap["Draw"]->setCheckable(true);
	addWidget(mToolButtonMap["Draw"].get());

	mToolButtonMap["Select"] = make_unique<QToolButton>();
	mToolButtonMap["Select"]->setText("Select");
	mToolButtonMap["Select"]->setCheckable(true);
	addWidget(mToolButtonMap["Select"].get());

	mToolButtonMap["Draw"]->setChecked(true);
	mToolButtonMap["Draw"]->setObjectName("Draw");
	mToolButtonMap["Select"]->setObjectName("Select");
}

scObjectSelectionToolBar::~scObjectSelectionToolBar()
{
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