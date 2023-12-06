#pragma once
#include <QToolBar>

class QVBoxLayout;
class QToolButton;
class ObjectSelectionToolBar : public QToolBar
{
public:
	ObjectSelectionToolBar(QWidget* parent = 0);

	const std::unique_ptr<QToolButton>& GetDrawButton() const;
	const std::unique_ptr<QToolButton>& GetSelectButton() const;

private:
	std::unique_ptr<QToolButton> mDrawButton;
	std::unique_ptr<QToolButton> mSelectButton;
};

