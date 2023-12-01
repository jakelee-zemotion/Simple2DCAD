#pragma once
#include "WidgetManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;
	mainWindow.setGeometry(200, 200, 600, 400);
	mainWindow.show();

	WidgetManager widgetManager;
	widgetManager.SetWidgets(mainWindow);

	return app.exec();
}