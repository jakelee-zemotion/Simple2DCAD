#pragma once
#include <QWidget>

class Viewport : public QWidget
{
public:
	Viewport(QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent* event) override;
};

