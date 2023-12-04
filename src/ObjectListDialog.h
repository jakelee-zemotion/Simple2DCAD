#pragma once
#include <QDialog>

class Shape;
class ObjectListDialog : public QDialog
{
public:
	ObjectListDialog(const QVector<Shape*>& mDrawObjects, QWidget* parent = 0);
};

