 #include "stdafx.h"
#include "conveyor.h"

Conveyor::Conveyor(Smp86xHandler* sh, QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::Conveyor())
	, smp86xHandler(sh)
{
	ui->setupUi(this);
	QSpinBox* spinBoxes[] = {
		ui->spinBox, ui->spinBox_2, ui->spinBox_3, 
		ui->spinBox_4, ui->spinBox_5, ui->spinBox_6, 
		ui->spinBox_7, ui->spinBox_8, ui->spinBox_9, 
		ui->spinBox_10, ui->spinBox_11, ui->spinBox_12, 
	};
	QSettings settings;
	for (int i=0; i<((sizeof(spinBoxes)/sizeof(QSpinBox*))); i++)
	{
		spinBoxes[i]->setValue(settings.value(QString("Conveyor/speed_%1").arg(i), 1000).toInt());
	}
	for (int i=0; i<((sizeof(spinBoxes)/sizeof(QSpinBox*))); i++)
	{
		connect(spinBoxes[i], SIGNAL(valueChanged(int)), this, SLOT(slotSpeedValueChanged(int)));
	}
#ifndef _OLD_VERSION
	ui->groupBox->setEnabled(false);
	ui->groupBox_2->setEnabled(false);
#endif
}

Conveyor::~Conveyor()
{
	delete ui;
}

void Conveyor::on_toolButton_pressed()
{
	smp86xHandler->start(1, ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value()/1000.0);
}

void Conveyor::on_toolButton_2_pressed()
{
	smp86xHandler->start(1, ui->spinBox->value(), -ui->spinBox_2->value(), ui->spinBox_3->value()/1000.0);
}

void Conveyor::on_toolButton_3_pressed()
{
	smp86xHandler->start(2, ui->spinBox_4->value(), ui->spinBox_5->value(), ui->spinBox_6->value()/1000.0);
}

void Conveyor::on_toolButton_4_pressed()
{
	smp86xHandler->start(2, ui->spinBox_4->value(), -ui->spinBox_5->value(), ui->spinBox_6->value()/1000.0);
}

void Conveyor::on_toolButton_5_pressed()
{
#ifdef _OLD_VERSION
	smp86xHandler->start(0, ui->spinBox_7->value(), ui->spinBox_8->value(), ui->spinBox_9->value()/1000.0);
#else
	smp86xHandler->start(2, ui->spinBox_7->value(), -ui->spinBox_8->value(), ui->spinBox_9->value() / 1000.0);
#endif // _OLD_VERSION
}

void Conveyor::on_toolButton_6_pressed()
{
#ifdef _OLD_VERSION
	smp86xHandler->start(0, ui->spinBox_7->value(), -ui->spinBox_8->value(), ui->spinBox_9->value()/1000.0);
#else
	smp86xHandler->start(2, ui->spinBox_7->value(), ui->spinBox_8->value(), ui->spinBox_9->value()/1000.0);
#endif // _OLD_VERSION
}

void Conveyor::on_toolButton_7_pressed()
{
	smp86xHandler->start(3, ui->spinBox_10->value(), ui->spinBox_11->value(), ui->spinBox_12->value() / 1000.0);
}

void Conveyor::on_toolButton_8_pressed()
{
	smp86xHandler->start(3, ui->spinBox_10->value(), -ui->spinBox_11->value(), ui->spinBox_12->value() / 1000.0);
}

void Conveyor::on_toolButton_released()
{
	smp86xHandler->stop(1);
}

void Conveyor::on_toolButton_2_released()
{
	smp86xHandler->stop(1);
}

void Conveyor::on_toolButton_3_released()
{
	smp86xHandler->stop(2);
}

void Conveyor::on_toolButton_4_released()
{
	smp86xHandler->stop(2);
}

void Conveyor::on_toolButton_5_released()
{
	smp86xHandler->stop(0);
}

void Conveyor::on_toolButton_6_released()
{
	smp86xHandler->stop(0);
}

void Conveyor::on_toolButton_7_released()
{
	smp86xHandler->stop(3);
}

void Conveyor::on_toolButton_8_released()
{
	smp86xHandler->stop(3);
}

void Conveyor::on_pushButton_clicked()
{
	QSettings settings;
	int valueAxisX = smp86xHandler->getSmp86xStatus().axis_status[0].logicPos;
	settings.setValue("Conveyor/XsetWide", valueAxisX);
	QMessageBox::information(this, QString::fromUtf16(L"提示"), QString::fromUtf16(L"X调宽脉冲已更改!"));
}
// void Conveyor::on_pushButton_clicked()		// 进板
// {
// 	
// }
// 
// void Conveyor::on_pushButton_2_clicked()	// 出板
// {
// 
// }

void Conveyor::slotSpeedValueChanged( int value )
{
	QSettings settings;
	QSpinBox* spinBoxes[] = {
		ui->spinBox, ui->spinBox_2, ui->spinBox_3, 
		ui->spinBox_4, ui->spinBox_5, ui->spinBox_6, 
		ui->spinBox_7, ui->spinBox_8, ui->spinBox_9, 
		ui->spinBox_10, ui->spinBox_11, ui->spinBox_12, 
	};
	for (int i=0; i<((sizeof(spinBoxes)/sizeof(QSpinBox*))); i++)
	{
		settings.setValue(QString("Conveyor/speed_%1").arg(i), spinBoxes[i]->value());
	}
}

// void Conveyor::on_pushButton_3_clicked()	// 重置
// {
// 
// }

// void Conveyor::on_pushButton_4_clicked()
// {
// 	int warn = QMessageBox::warning(this,QString::fromUtf16(L"警告"), QString::fromUtf16(L"是否要回原点？"), QString::fromUtf16(L"是"), QString::fromUtf16(L"取消"));
// 	if(warn = 1)
// 	smp86xHandler->home(0);
// }

