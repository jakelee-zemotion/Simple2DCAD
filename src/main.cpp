#pragma once
#include "scMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	scMainWindow mainWindow;
	mainWindow.setGeometry(200, 200, 600, 500);
	mainWindow.SetWidgets();
	mainWindow.show();

	return app.exec();
}