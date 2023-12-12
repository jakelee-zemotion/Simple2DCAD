#pragma once

#include <QDialog>

class scShapeList;
class scObjectListDialog : public QDialog
{
public:
	scObjectListDialog(const scShapeList& shapeObjects, QWidget* parent = 0);
};

