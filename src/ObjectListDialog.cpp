#include "ObjectListDialog.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

ObjectListDialog::ObjectListDialog(QWidget* parent)
	:QDialog(parent)
{
	QVBoxLayout* layout = new QVBoxLayout();
	QTableView* qq = new QTableView();

	this->setLayout(layout);
	layout->addWidget(qq);

	QStandardItemModel* qm = new QStandardItemModel(4, 4);
	qq->setModel(qm);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			QModelIndex index = qm->index(i, j, QModelIndex());
			qm->setData(index, 0);
		}
	}
}
