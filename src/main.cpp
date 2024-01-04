#pragma once

// qt
#include <QtWidgets/QApplication>

// Simple2DCAD
#include "scMainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	scMainWindow mainWindow;
	mainWindow.setGeometry(100, 100, 500, 500);
	mainWindow.SetWidgets();
	mainWindow.show();

	return app.exec();
}