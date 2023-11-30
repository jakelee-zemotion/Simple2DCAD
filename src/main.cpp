#pragma once

#include <QtWidgets/QApplication>
#include <QMainWindow>

#include "Viewport.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;
	mainWindow.setGeometry(200, 200, 500, 300);
	mainWindow.show();

	Viewport* viewport = new Viewport();
	mainWindow.setCentralWidget(viewport);

	return app.exec();
}