#pragma once
#include "ShapeVector.h"

#include <QDialog>

class Shape;
class ObjectListDialog : public QDialog
{
public:
	ObjectListDialog(ShapeVector& mDrawObjects, QWidget* parent = 0);
};

