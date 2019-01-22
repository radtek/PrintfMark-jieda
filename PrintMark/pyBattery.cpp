#include "stdafx.h"
#include "pyBattery.h"

pyBattery::pyBattery(QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::MSWindowsFixedSizeDialogHint)
{
	ui.setupUi(this);
}

pyBattery::~pyBattery()
{
}
