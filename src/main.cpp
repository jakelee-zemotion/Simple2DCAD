#pragma once

#include <QtWidgets/QApplication>
#include <QMainWindow>

#include "Viewport.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;
	mainWindow.show();

	Viewport* viewport = new Viewport();
	mainWindow.setCentralWidget(viewport);

	return app.exec();
}