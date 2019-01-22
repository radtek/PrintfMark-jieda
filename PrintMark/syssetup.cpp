#include "stdafx.h"
#include "syssetup.h"
#include "ui_syssetup.h"
#include <QSerialPortInfo>

SysSetup::SysSetup(QWidget *parent)
	: QDialog(parent, Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::SysSetup())
{
	ui->setupUi(this);

	QSettings settings;
	auto portList = QSerialPortInfo::availablePorts();
	foreach( const QSerialPortInfo& port, portList )
	{
		ui->comboBox->addItem( port.portName() );
		ui->comboBox->setItemData(ui->comboBox->count()-1, port.portName());
		ui->comboBox_2->addItem(port.portName());
		ui->comboBox_2->setItemData(ui->comboBox_2->count() - 1, port.portName());
		ui->comboBox_3->addItem( port.portName() );
		ui->comboBox_3->setItemData(ui->comboBox_3->count()-1, port.portName());
	}
	ui->comboBox->setCurrentText(settings.value("Smp86x/port1", "COM1").toString());
	ui->comboBox_2->setCurrentText(settings.value("Smp86x/port2", "COM2").toString());
	ui->comboBox_3->setCurrentIndex(ui->comboBox_3->findData(settings.value("Print/port", "COM3").toString()));
	int port_mode = settings.value("port_mode", 0).toInt();
	ui->radioButton->setChecked(port_mode == 0);
	ui->radioButton_2->setChecked(port_mode == 1);

	ui->lineEdit->setText(settings.value("Tcp/ip", "192.168.1.10").toString());
	ui->lineEdit_2->setText(settings.value("Tcp/port", 16000).toString());

	ui->pulseValueX->setText(settings.value("PulseEquivalent0/0", 0.02).toString());
	ui->pulseValueY->setText(settings.value("PulseEquivalent0/1", 0.02).toString());
	ui->pulseValueZ->setText(settings.value("PulseEquivalent0/2", 0.02).toString());
	ui->pulseValueU->setText(settings.value("PulseEquivalent0/3", 0.02).toString());
	ui->pulseValueX->setValidator(new QRegExpValidator(QRegExp("^(\\d+\\.?\\d*)|(\\.\\d+)$"), ui->pulseValueX));
	ui->pulseValueY->setValidator(new QRegExpValidator(QRegExp("^(\\d+\\.?\\d*)|(\\.\\d+)$"), ui->pulseValueY));
	ui->pulseValueZ->setValidator(new QRegExpValidator(QRegExp("^(\\d+\\.?\\d*)|(\\.\\d+)$"), ui->pulseValueZ));
	ui->pulseValueU->setValidator(new QRegExpValidator(QRegExp("^(\\d+\\.?\\d*)|(\\.\\d+)$"), ui->pulseValueU));
	//ui->spinBox->setValue(settings.value("Delay/snap", 50).toInt());
	ui->doubleSpinBox->setValue(settings.value("Smp86x/safe_z").toDouble());
	ui->spinBox->setValue(settings.value("Timer/inteval", 30).toInt());
	ui->checkBox->setChecked(settings.value("door_stop", false).toBool());
	ui->spinBox_2->setValue(settings.value("Smp86x/speed_ratio", 50).toInt());
	ui->spinBox_3->setValue(settings.value("Maintain/duration", 360).toInt());
}

SysSetup::~SysSetup()
{
	delete ui;
}

void SysSetup::accept()
{
	QSettings settings;
	settings.setValue("Smp86x/port1", ui->comboBox->currentText());
	settings.setValue("Smp86x/port2", ui->comboBox_2->currentText());
	settings.setValue("Print/port", ui->comboBox_3->currentText());
	settings.setValue("PulseEquivalent0/0", ui->pulseValueX->text());
	settings.setValue("PulseEquivalent0/1", ui->pulseValueY->text());
	settings.setValue("PulseEquivalent0/2", ui->pulseValueZ->text());
	settings.setValue("PulseEquivalent0/3", ui->pulseValueU->text());
	//settings.setValue("Delay/snap", ui->spinBox->value());
	settings.setValue("Smp86x/safe_z", ui->doubleSpinBox->value());
	settings.setValue("port_mode", ui->radioButton->isChecked() ? 0 : 1);
	settings.setValue("Tcp/ip", ui->lineEdit->text());
	settings.setValue("Tcp/port", ui->lineEdit_2->text());
	settings.setValue("Timer/inteval", ui->spinBox->value());
	settings.setValue("door_stop", ui->checkBox->isChecked());
	settings.setValue("Smp86x/speed_ratio", ui->spinBox_2->value());
	settings.setValue("Maintain/duration", ui->spinBox_3->value());
	QDialog::accept();
}

