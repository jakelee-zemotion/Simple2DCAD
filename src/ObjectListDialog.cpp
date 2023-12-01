#include "ObjectListDialog.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

ObjectListDialog::ObjectListDialog(QVector<Shape*>& mDrawObjects, QWidget* parent)
	:QDialog(parent)
{
	QVBoxLayout* layout = new QVBoxLayout();
	QTableView* qq = new QTableView();

	this->setLayout(layout);
	layout->addWidget(qq);

	QStandardItemModel* qm = new QStandardItemModel(mDrawObjects.size(), 2);
	qq->setModel(qm);

	for (int i = 0; i < qm->rowCount(); i++)
	{
		for (int j = 0; j < qm->columnCount(); j++)
		{
			QModelIndex index = qm->index(i, j, QModelIndex());
			qm->setData(index, 0);
		}
	}
}
