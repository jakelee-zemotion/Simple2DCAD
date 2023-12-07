#pragma once
#include "scShapeVector.h"

#include <QDialog>

class scObjectListDialog : public QDialog
{
public:
	scObjectListDialog(scShapeVector& shapeObjects, QWidget* parent = 0);
};

