#pragma once
#include "ShapeList.h"

#include <QDialog>

class Shape;
class ObjectListDialog : public QDialog
{
public:
	ObjectListDialog(ShapeList& shapeObjects, QWidget* parent = 0);
};

