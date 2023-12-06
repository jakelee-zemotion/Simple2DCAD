#include "ObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

using namespace std;

ObjectSelectionToolBar::ObjectSelectionToolBar(QWidget* parent)
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
}

ObjectSelectionToolBar::~ObjectSelectionToolBar()
{
}

void ObjectSelectionToolBar::ConnectToolButton(QObject* widgetManager)
{
	connect(mToolButtonMap["Draw"].get(), SIGNAL(clicked()), widgetManager, SLOT(PressDrawMode()));
	connect(mToolButtonMap["Select"].get(), SIGNAL(clicked()), widgetManager, SLOT(PressSelectMode()));
}

bool ObjectSelectionToolBar::SetButtonPressed(string name)
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