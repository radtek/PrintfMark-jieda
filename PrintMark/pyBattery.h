#pragma once

#include <QWidget>
#include "ui_pyBattery.h"

class pyBattery : public QWidget
{
	Q_OBJECT

public:
	pyBattery(Smp86xHandler* sh, Smp86xHandler* sh2, QWidget *parent = Q_NULLPTR);
	~pyBattery();

	
private:
	Ui::pyBattery ui;
	Smp86xHandler* smp86xHandler;
	Smp86xHandler* smp86xHandler2;
	ushort data[2];
	float electr;
	void timeoutshow();
};


