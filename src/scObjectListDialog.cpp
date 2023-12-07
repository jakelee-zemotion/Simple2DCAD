#include "scObjectListDialog.h"
#include "scShapeList.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

scObjectListDialog::scObjectListDialog(scShapeList& shapeObjects, QWidget* parent)
	:QDialog(parent)
{
	QVBoxLayout* layout = new QVBoxLayout();
	QTableView* qq = new QTableView();

	this->setLayout(layout);
	layout->addWidget(qq);

	QStandardItemModel* qm = new QStandardItemModel(shapeObjects.mPolygonList.size(), 2);
	qq->setModel(qm);

	for (int i = 0; i < qm->rowCount(); i++)
	{
		for (int j = 0; j < qm->columnCount(); j++)
		{
			QModelIndex index = qm->index(i, j, QModelIndex());
			//qm->setData(index, shapeObjects.mShapes[i]->name);
		}
	}
}
