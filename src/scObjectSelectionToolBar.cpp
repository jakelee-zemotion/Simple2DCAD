#include "scObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

#include <string>

using namespace std;

scObjectSelectionToolBar::scObjectSelectionToolBar(QWidget* parent)
	:QToolBar(parent)
{
}

scObjectSelectionToolBar::~scObjectSelectionToolBar()
{
}

void scObjectSelectionToolBar::AddToolButton(const string& name)
{
	string iconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/DrawLine.png";//+ name + ".png";
	QIcon icon("C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/DrawLine.png");

	mToolButtonMap[name] = make_unique<QToolButton>();
	mToolButtonMap[name]->setText(QString::fromStdString(name));
	mToolButtonMap[name]->setCheckable(true);
	mToolButtonMap[name]->setObjectName(name);
	mToolButtonMap[name]->setIcon(icon);
	addWidget(mToolButtonMap[name].get());
}

void scObjectSelectionToolBar::SetCurrentToolButton(const string& name)
{
	mToolButtonMap[name]->setChecked(true);
}

void scObjectSelectionToolBar::ConnectToolButton(const string& name)
{
	connect(mToolButtonMap[name].get(), SIGNAL(clicked()), this, SLOT(ClickToolButton()));
}

void scObjectSelectionToolBar::ConnectTransitSignal(const QObject* widgetManager)
{
	connect(this, SIGNAL(PressToolButton(std::string)), widgetManager, SLOT(TransitState(std::string)));
}

void scObjectSelectionToolBar::ClickToolButton()
{
	QObject* obj = sender();
	string a = obj->objectName().toStdString();
	emit PressToolButton(obj->objectName().toStdString());
}

bool scObjectSelectionToolBar::SetButtonPressed(const string& name)
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
