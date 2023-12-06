#pragma once
#include <QToolBar>

class QVBoxLayout;
class ObjectSelectionToolBar : public QToolBar
{
public:
	ObjectSelectionToolBar(QWidget* parent = 0);

private:
	std::unique_ptr<QToolButton> mDrawButton;
	std::unique_ptr<QToolButton> mSelectButton;
};

