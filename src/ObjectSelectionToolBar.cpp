#include "ObjectSelectionToolBar.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

using namespace std;

ObjectSelectionToolBar::ObjectSelectionToolBar(QWidget* parent)
	:QToolBar(parent)
{
	mDrawButton = make_unique<QToolButton>();

	mDrawButton->setText("Draw");
	addWidget(mDrawButton.get());
	/*mDrawButton->setCheckable(true);
	mDrawButton->setChecked(true);*/

	mSelectButton = make_unique<QToolButton>();
	mSelectButton->setText("Select");
	addWidget(mSelectButton.get());
}
