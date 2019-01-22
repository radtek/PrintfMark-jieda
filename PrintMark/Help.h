#pragma once

#include <QDialog>
#include "ui_Help.h"

class Help : public QDialog
{
	Q_OBJECT

public:
	Help(QWidget *parent = Q_NULLPTR);
	~Help();

private:
	Ui::Help ui;
};
