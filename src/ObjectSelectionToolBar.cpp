#include "ObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

ObjectSelectionToolBar::ObjectSelectionToolBar(QWidget* parent)
	:QToolBar(parent)
{
	QToolButton* mToolButton = new QToolButton();
	mToolButton->setText("hi");
	addWidget(mToolButton);
}
