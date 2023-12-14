#pragma once

#include <QDialog>

class scScene;
class scObjectListDialog : public QDialog
{
public:
	scObjectListDialog(const scScene& scene, QWidget* parent = 0);
};

