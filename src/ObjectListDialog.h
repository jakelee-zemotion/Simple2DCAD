#pragma once
#include <QDialog>

class Shape;
class ObjectListDialog : public QDialog
{
public:
	ObjectListDialog(QVector<Shape*>& mDrawObjects, QWidget* parent = 0);
};

