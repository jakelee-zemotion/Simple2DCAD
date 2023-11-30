#pragma once

#include <QtWidgets/QApplication>
#include <QMainWindow>

#include "Viewport.h"
#include "ObjectSelectionToolBar.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;
	mainWindow.setGeometry(200, 200, 600, 400);
	mainWindow.show();

	Viewport* viewport = new Viewport();
	mainWindow.setCentralWidget(viewport);

	ObjectSelectionToolBar* objSelectToolBar = new ObjectSelectionToolBar();
	mainWindow.addToolBar(Qt::LeftToolBarArea, objSelectToolBar);

	return app.exec();
}