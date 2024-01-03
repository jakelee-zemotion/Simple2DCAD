#include "scToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

#include <string>

using namespace std;

scToolBar::scToolBar(QWidget* parent)
	:QToolBar(parent)
{
	// FileToolButton
	// 1. New Scene
	string newSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/NewScene.jpg";
	QIcon newSceneIcon = QIcon(QString::fromStdString(newSceneIconDir));

	mNewSceneToolButton = make_unique<QToolButton>();
	mNewSceneToolButton->setIcon(newSceneIcon);
	addWidget(mNewSceneToolButton.get());
	connect(mNewSceneToolButton.get(), SIGNAL(clicked()), parent, SLOT(NewScene()));

	// 2. Open Scene
	string openSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/OpenScene.jpg";
	QIcon openSceneIcon = QIcon(QString::fromStdString(openSceneIconDir));

	mOpenSceneToolButton = make_unique<QToolButton>();
	mOpenSceneToolButton->setIcon(openSceneIcon);
	addWidget(mOpenSceneToolButton.get());
	connect(mOpenSceneToolButton.get(), SIGNAL(clicked()), parent, SLOT(OpenScene()));

	// 3. Save Scene
	string saveSceneIconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/SaveScene.png";
	QIcon saveSceneIcon = QIcon(QString::fromStdString(saveSceneIconDir));

	mSaveSceneToolButton = make_unique<QToolButton>();
	mSaveSceneToolButton->setIcon(saveSceneIcon);
	addWidget(mSaveSceneToolButton.get());
	connect(mSaveSceneToolButton.get(), SIGNAL(clicked()), parent, SLOT(SaveScene()));

	addSeparator();
}

scToolBar::~scToolBar()
{
}

void scToolBar::AddEditToolButton(const string& name)
{
	string iconDir = "C:/Users/Jake/Desktop/code/Simple2DCAD/img/icon/toolBar/" + name + ".png";
	QIcon icon(QString::fromStdString(iconDir));

	mEditToolButtonMap[name] = make_unique<QToolButton>();
	mEditToolButtonMap[name]->setText(QString::fromStdString(name));
	mEditToolButtonMap[name]->setCheckable(true);
	mEditToolButtonMap[name]->setObjectName(name);
	mEditToolButtonMap[name]->setIcon(icon);
	addWidget(mEditToolButtonMap[name].get());
}

void scToolBar::SetCurrentToolButton(const string& name)
{
	mEditToolButtonMap[name]->setChecked(true);
}

void scToolBar::ConnectToolButton(const string& name)
{
	connect(mEditToolButtonMap[name].get(), SIGNAL(clicked()), this, SLOT(ClickToolButton()));
}

void scToolBar::ConnectTransitSignal(const QObject* mainWindow)
{
	connect(this, SIGNAL(PressToolButton(std::string)), mainWindow, SLOT(TransitState(std::string)));
}

void scToolBar::ClickToolButton()
{
	QObject* obj = sender();
	string a = obj->objectName().toStdString();
	emit PressToolButton(obj->objectName().toStdString());
}

bool scToolBar::SetButtonPressed(const string& name)
{
	// If name button is pressed, return false.
	if (!mEditToolButtonMap[name]->isChecked())
	{
		mEditToolButtonMap[name]->setChecked(true);
		return false;
	}


	for (const auto& button : mEditToolButtonMap)
	{
		button.second->setChecked(false);
	}

	mEditToolButtonMap[name]->setChecked(true);

	return true;
}