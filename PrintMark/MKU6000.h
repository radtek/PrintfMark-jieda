#pragma once

#include <QDialog>
#include "ui_MKU6000.h"

class MKU6000 : public QDialog
{
	Q_OBJECT

public:
	MKU6000(QWidget *parent = Q_NULLPTR);
	~MKU6000();

private:
	Ui::MKU6000 ui;
};
