#include "stdafx.h"
#include "pyBattery.h"

pyBattery::pyBattery(Smp86xHandler* sh,Smp86xHandler* sh2, QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::MSWindowsFixedSizeDialogHint)
	, smp86xHandler(sh)
	,smp86xHandler2(sh2)
{
	ui.setupUi(this);
	QTimer* timer = new QTimer(this);
	timeoutshow();
	connect(timer, &QTimer::timeout, this, &pyBattery::timeoutshow);
	timer->start(5000);
}

pyBattery::~pyBattery()
{
}

void pyBattery::timeoutshow()
{
	smp86xHandler->readRawData(0x0E, 2, data);
	//ushort a, b;
	//long c;
	//c = (a << sizeof(ushort) * 8) | b;
	short tempdata = data[0];
	data[0] = data[1];
	data[1] = tempdata;
	electr = *(float*)data;
	QString elect = QString::number(electr);
	ui.lineEdit->setText(elect);
}
