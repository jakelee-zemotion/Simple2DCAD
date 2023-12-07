#pragma once

#include <QDialog>

class scShapeList;
class scObjectListDialog : public QDialog
{
public:
	scObjectListDialog(scShapeList& shapeObjects, QWidget* parent = 0);
};

