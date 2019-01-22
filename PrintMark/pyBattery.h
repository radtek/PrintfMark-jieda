#pragma once

#include <QWidget>
#include "ui_pyBattery.h"

class pyBattery : public QWidget
{
	Q_OBJECT

public:
	pyBattery(QWidget *parent = Q_NULLPTR);
	~pyBattery();

private:
	Ui::pyBattery ui;
};
