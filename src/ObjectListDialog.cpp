#include "ObjectListDialog.h"
#include "Shape.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

ObjectListDialog::ObjectListDialog(ShapeVector& shapeObjects, QWidget* parent)
	:QDialog(parent)
{
	QVBoxLayout* layout = new QVBoxLayout();
	QTableView* qq = new QTableView();

	this->setLayout(layout);
	layout->addWidget(qq);

	QStandardItemModel* qm = new QStandardItemModel(shapeObjects.size(), 2);
	qq->setModel(qm);

	for (int i = 0; i < qm->rowCount(); i++)
	{
		for (int j = 0; j < qm->columnCount(); j++)
		{
			QModelIndex index = qm->index(i, j, QModelIndex());
			qm->setData(index, shapeObjects[i]->name);
		}
	}
}
