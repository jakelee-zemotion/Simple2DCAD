#pragma once
#include "ShapeVector.h"

#include <QDialog>

class Shape;
class ObjectListDialog : public QDialog
{
public:
	ObjectListDialog(ShapeVector& shapeObjects, QWidget* parent = 0);
};

