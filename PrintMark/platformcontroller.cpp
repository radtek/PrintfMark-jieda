#include "StdAfx.h"
#include "platformcontroller.h"
#include "ui_platformcontroller.h"
#include <boost/bind/bind.hpp>

const double ratio[] = {0.004, 0.05, 0.20, 0.70, 1.0};
const double ratio1[] = {1.0, 1.0, 0.1};
extern int speedValue[];

PlatformController::PlatformController(Smp86xHandler* _smp86xHandler[], QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint|Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint)
{
	this->smp86xHandler[0] = _smp86xHandler[0];
	this->smp86xHandler[1] = _smp86xHandler[1];
	p_id = 0;
	speedText << QString::fromUtf16(L"慢速") << QString::fromUtf16(L"较慢")
		<< QString::fromUtf16(L"中速") << QString::fromUtf16(L"较快") 
		<< QString::fromUtf16(L"快速");
	ui = (decltype(ui))(new Ui::PlatformController);
	((Ui::PlatformController *)ui)->setupUi(this);
	ui->label_17->hide();
	ui->label_19->hide();
	ui->label_21->hide();
	ui->label_23->hide();
	ui->buttonHome->addAction(ui->actionHomeX2);

	QSettings settings;
	ui->sliderSpeed->setValue(settings.value("Smp86x/speed_index", 0).toInt());
	ui->checkBox->setChecked(settings.value("Smp86x/step", false).toBool());

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
	timer->start(200);
}

PlatformController::~PlatformController()
{
	QSettings settings;
	settings.setValue("Smp86x/speed_index", ui->sliderSpeed->value());
	settings.setValue("Smp86x/step", ui->checkBox->isChecked());
	delete ui;
}

void PlatformController::on_sliderSpeed_valueChanged( int value )
{
	QSettings settings;
	ui->groupBoxSpeed->setTitle(speedText[value]);
}

void PlatformController::on_buttonLeft_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoX->text().toDouble()/pulseEquivalent[0];
		int runSpeed = speedValue[1]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(0, -pos, runSpeed/5, runSpeed, speedValue[2]/1000.0);
		return;
	}

	int runSpeed = speedValue[1]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(0, runSpeed/5, -runSpeed, speedValue[2]/1000.0);
}

void PlatformController::on_buttonLeft_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(0);
}

void PlatformController::on_buttonUp_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoY->text().toDouble()/pulseEquivalent[1];
		int runSpeed = speedValue[4]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(1, pos, runSpeed/5, runSpeed, speedValue[5]/1000.0);
		return;
	}

	int runSpeed = speedValue[4]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(1, runSpeed/5, runSpeed, speedValue[5]/1000.0);
}

void PlatformController::on_buttonUp_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(1);
}

void PlatformController::on_buttonRight_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoX->text().toDouble()/pulseEquivalent[0];
		int runSpeed = speedValue[1]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(0, pos, runSpeed/5, runSpeed, speedValue[2]/1000.0);
		return;
	}

	int runSpeed = speedValue[1]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(0, runSpeed/5, runSpeed, speedValue[2]/1000.0);
}

void PlatformController::on_buttonRight_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(0);
}

void PlatformController::on_buttonDown_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoY->text().toDouble()/pulseEquivalent[1];
		int runSpeed = speedValue[4]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(1, -pos, runSpeed/5, runSpeed, speedValue[5]/1000.0);
		return;
	}

	int runSpeed = speedValue[4]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(1, runSpeed/5, -runSpeed, speedValue[5]/1000.0);
}

void PlatformController::on_buttonDown_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(1);
}

void PlatformController::on_buttonZup_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoZ->text().toDouble()/pulseEquivalent[2];
		int runSpeed = speedValue[7]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(2, pos, runSpeed/5, runSpeed, speedValue[8]/1000.0);
		return;
	}

	int runSpeed = speedValue[7]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, runSpeed/5, runSpeed, speedValue[8]/1000.0);
}

void PlatformController::on_buttonZup_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(2);
}

void PlatformController::on_buttonZdown_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoZ->text().toDouble()/pulseEquivalent[2];
		int runSpeed = speedValue[7]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(2, pos, runSpeed/5, runSpeed, speedValue[8]/1000.0);
		return;
	}

	int runSpeed = speedValue[7]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, runSpeed/5, -runSpeed, speedValue[8]/1000.0);
}

void PlatformController::on_buttonZdown_released()
{
	if (!ui->checkBox->isChecked())
	{
		smp86xHandler[0]->stop(2);
	}
}

void PlatformController::on_buttonUup_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoU->text().toDouble()/pulseEquivalent[3];
		int runSpeed = speedValue[10]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(2, pos, runSpeed/5, runSpeed, speedValue[11]/1000.0);
		return;
	}

	int runSpeed = speedValue[10]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, runSpeed/5, runSpeed, speedValue[11]/1000.0);
}

void PlatformController::on_buttonUup_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(2);
}

void PlatformController::on_buttonUdown_pressed()
{
	QSettings settings;
	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	if (ui->checkBox->isChecked())
	{
		double pulseEquivalent[4];
		for (int i=0; i<4; i++)
		{
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
		}
		int pos = ui->gotoU->text().toDouble()/pulseEquivalent[3];
		int runSpeed = speedValue[10]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
		smp86xHandler[0]->start(2, -pos, runSpeed/5, runSpeed, speedValue[11]/1000.0);
		return;
	}

	int runSpeed = speedValue[10]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, runSpeed/5, -runSpeed, speedValue[11]/1000.0);
}

void PlatformController::on_buttonUdown_released()
{
	if (!ui->checkBox->isChecked())
		smp86xHandler[0]->stop(2);
}

void PlatformController::on_buttonGotoX_clicked()
{
	QSettings settings;

	double pulseEquivalent[4];
	for (int i=0; i<4; i++)
	{
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
	}
	//double runSpeed = settings.value("Smp86x/base_speed", 25).toDouble();
	//double accelerationTime = settings.value("Smp86x/acceleration_time", 10).toInt()/1000.0;

	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
	//double safe_z = settings.value("Smp86x/safe_height", 0.0).toDouble();
	//if(ss.axis_status[2].logicPos*pulseEquivalent[2] > safe_z)
	//{
	//	QMessageBox::information(this, QString::fromUtf16(L"警告"), QString::fromUtf16(L"不在安全高度"));
	//	return;
	//}

	int pos = 0;
	double gotoPos;
	gotoPos = ui->gotoX->text().toDouble();

	pos = ss.axis_status[0].logicPos;
	pos = gotoPos/pulseEquivalent[0] - pos;

	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	int runSpeed = speedValue[1]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(0, pos, runSpeed/5, runSpeed, speedValue[2]/1000.0);
}

void PlatformController::on_buttonGotoY_clicked()
{
	QSettings settings;

	double pulseEquivalent[4];
	for (int i=0; i<4; i++)
	{
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
	}
	//double runSpeed = settings.value("Smp86x/base_speed", 25).toDouble();
	//double accelerationTime = settings.value("Smp86x/acceleration_time", 10).toInt()/1000.0;

	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
	//double safe_z = settings.value("Smp86x/safe_height", 0.0).toDouble();
	//if(ss.axis_status[2].logicPos*pulseEquivalent[2] > safe_z)
	//{
	//	QMessageBox::information(this, QString::fromUtf16(L"警告"), QString::fromUtf16(L"不在安全高度"));
	//	return;
	//}

	int pos;
	double gotoPos;
	gotoPos = ui->gotoY->text().toDouble();


	pos = ss.axis_status[1].logicPos;
	pos = gotoPos/pulseEquivalent[1] - pos;

	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	int runSpeed = speedValue[4]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(1, pos, runSpeed/5, runSpeed, speedValue[5]/1000.0);
	//Smp86x::start(slave, 1, pos, runSpeed/5/pulseEquivalentY, runSpeed/pulseEquivalentY, accelerationTime);
}

void PlatformController::on_buttonGotoZ_clicked()
{
	QSettings settings;
	double pulseEquivalent[4];
	for (int i=0; i<4; i++)
	{
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
	}
	//double runSpeed = settings.value("Smp86x/z_speed", 25).toDouble();
	//double accelerationTime = settings.value("Smp86x/acceleration_time", 40).toInt()/1000.0;

	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();

	int pos;
	double gotoPos;
	//gotoPos = ui->gotoZ->text().toDouble();
	gotoPos = ui->gotoZ->text().toDouble();

	pos = ss.axis_status[2].logicPos;
	pos = gotoPos/pulseEquivalent[2] - pos;

	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	int runSpeed = speedValue[7]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, pos, runSpeed/5, runSpeed, speedValue[8]/1000.0);
	//Smp86x::start(slave, 2, pos, runSpeed/5/pulseEquivalentZ, runSpeed/pulseEquivalentZ, 0.1);
}

void PlatformController::on_buttonGotoU_clicked()
{
	QSettings settings;
	double pulseEquivalent[4];
	for (int i=0; i<4; i++)
	{
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
	}
	//double runSpeed = settings.value("Smp86x/u_speed", 25).toDouble();
	//double accelerationTime = settings.value("Smp86x/acceleration_time", 40).toInt()/1000.0;

	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();

	//double safeHeight[8];
	//safeHeight[0] = settings.value("SafeHeight/0").toDouble();
	//safeHeight[1] = settings.value("SafeHeight/1").toDouble();
	//safeHeight[2] = settings.value("SafeHeight/2").toDouble();
	//safeHeight[3] = settings.value("SafeHeight/3").toDouble();
	//safeHeight[4] = settings.value("SafeHeight/4").toDouble();
	//safeHeight[5] = settings.value("SafeHeight/5").toDouble();
	//safeHeight[6] = settings.value("SafeHeight/6").toDouble();
	//safeHeight[7] = settings.value("SafeHeight/7").toDouble();

	//if(ss.axis_status[2].logicPos*pulseEquivalent[2] > 0)
	//{
	//	QMessageBox::information(this, QString::fromUtf16(L"警告"), QString::fromUtf16(L"不在安全高度"));
	//	return;
	//}

	int pos;
	double gotoPos;
	//gotoPos = ui->gotoU->text().toDouble();
	gotoPos = ui->gotoU->text().toDouble();


	pos = ss.axis_status[2].logicPos;
	pos = gotoPos/pulseEquivalent[3] - pos;

	double speed_ratio = settings.value("Smp86x/speed_ratio", 50).toInt()/100.0;
	int runSpeed = speedValue[10]*ratio[ui->sliderSpeed->value()]*ratio1[p_id]*speed_ratio;
	smp86xHandler[0]->start(2, pos, runSpeed/5, runSpeed, speedValue[11]/1000.0);
}

void PlatformController::on_buttonHome_clicked()
{
	emit reset();
}

void PlatformController::on_buttonStop_clicked()
{
	smp86xHandler[0]->stopAll();
	smp86xHandler[1]->stopAll();
}

void PlatformController::on_actionHomeX2_triggered()
{
	smp86xHandler[1]->home(0);
}

void PlatformController::slotTimeout()
{
	static const char* statusStyles[] = {
		"font: 10pt \"Webdings\";color: red;", 
		"font: 10pt \"Webdings\";color: green;",
		"font: 10pt \"Webdings\";color: gold;"
	};

	static const char* btnStyle = "QToolButton {\n	border: 1px solid #707070;\n    background-color: rgb(255,0,0);\n}\n";

	QSettings settings;
	SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus(), };

	double pulseEquivalent[4];
	for (int i=0; i<4; i++)
	{
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(p_id).arg(i), 0.01).toDouble();
	}

	ui->labelPosX->setText(QString("%1").arg(ss[0].axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
	ui->labelPosY->setText(QString("%1").arg(ss[0].axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
#ifdef _OLD_VERSION
	//ui->labelPosZ->setText(QString("%1").arg(ss[0].axis_status[2].logicPos*pulseEquivalent[2], 0, 'f', 3));
	ui->labelPosU->setText(QString("%1").arg(ss[0].axis_status[2].logicPos*pulseEquivalent[3], 0, 'f', 3));
#endif // _OLD_VERSION

	short state = 0; for(int i=0; i<3; i++) state |= ss[0].axis_status[i].state;
	//state |= ss[1].axis_status[3].state;
	ui->labelStatus->setStyleSheet(statusStyles[(state & 0x0080) ? 0 :(1+bool(state&0x01))]);

#if 0
	double safe_z = settings.value("Smp86x/safe_z", 0.0).toDouble();
	if(ss[0].axis_status[2].logicPos*pulseEquivalent[2] < safe_z)
	{
		ui->buttonLeft->setEnabled(false);
		ui->buttonRight->setEnabled(false);
		ui->buttonUp->setEnabled(false);
		ui->buttonDown->setEnabled(false);
		ui->buttonUup->setEnabled(false);
		ui->buttonUdown->setEnabled(false);
		ui->buttonGotoX->setEnabled(false);
		ui->buttonGotoY->setEnabled(false);
		ui->buttonGotoU->setEnabled(false);
		//ui->buttonLeft->setStyleSheet(btnStyle);
		//ui->buttonRight->setStyleSheet(btnStyle);
		//ui->buttonUp->setStyleSheet(btnStyle);
		//ui->buttonDown->setStyleSheet(btnStyle);
		//ui->buttonUup->setStyleSheet(btnStyle);
		//ui->buttonUdown->setStyleSheet(btnStyle);
		//ui->buttonGotoX->setStyleSheet(btnStyle);
		//ui->buttonGotoY->setStyleSheet(btnStyle);
		//ui->buttonGotoU->setStyleSheet(btnStyle);
	}
	else
	{
		ui->buttonLeft->setEnabled(true);
		ui->buttonRight->setEnabled(true);
		ui->buttonUp->setEnabled(true);
		ui->buttonDown->setEnabled(true);
		ui->buttonUup->setEnabled(true);
		ui->buttonUdown->setEnabled(true);
		ui->buttonGotoX->setEnabled(true);
		ui->buttonGotoY->setEnabled(true);
		ui->buttonGotoU->setEnabled(true);
		//ui->buttonLeft->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonRight->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonUp->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonDown->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonUup->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonUdown->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonGotoX->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonGotoY->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
		//ui->buttonGotoU->setStyleSheet("QToolButton {border: 1px solid #acacac;background-color: rgb(230, 230, 230);}");
	}
#endif // 0
}

void PlatformController::keyPressEvent( QKeyEvent *event )
{
	if (!event->isAutoRepeat())
	{
		switch(event->key())
		{
		case Qt::Key_Left:
			on_buttonLeft_pressed();
			break;;
		case Qt::Key_Right:
			on_buttonRight_pressed();
			break;
		case Qt::Key_Up:
			on_buttonUp_pressed();
			break;
		case Qt::Key_Down:
			on_buttonDown_pressed();
			break;
		case Qt::Key_PageUp:
			on_buttonZup_pressed();
			break;
		case Qt::Key_PageDown:
			on_buttonZdown_pressed();
			break;
		case Qt::Key_Home:
			on_buttonUup_pressed();
			break;
		case Qt::Key_End:
			on_buttonUdown_pressed();
			break;
		}
	}

	if (event->key() == Qt::Key_Plus)
	{
		ui->sliderSpeed->setValue(ui->sliderSpeed->value()+1);
	}
	if (event->key() == Qt::Key_Minus)
	{
		ui->sliderSpeed->setValue(ui->sliderSpeed->value()-1);
	}
}

void PlatformController::keyReleaseEvent( QKeyEvent *event )
{
	if (!event->isAutoRepeat())
	{
		switch(event->key())
		{
		case Qt::Key_Left:
		case Qt::Key_Right:
			smp86xHandler[0]->stop(0);
			break;
		case Qt::Key_Up:
		case Qt::Key_Down:
			smp86xHandler[0]->stop(1);
			break;
// 		case Qt::Key_PageUp:
// 		case Qt::Key_PageDown:
// 			smp86xHandler[0]->stop(2);
// 			break;
		case Qt::Key_Home:
		case Qt::Key_End:
			smp86xHandler[1]->stop(2);
			break;
		}
	}
}

void PlatformController::closeEvent( QCloseEvent *e )
{
	return QWidget::closeEvent(e);
}

void PlatformController::mouseDoubleClickEvent( QMouseEvent *event )
{
	if (ui->labelPosX->rect().contains(ui->labelPosX->mapFromGlobal(event->globalPos())))
		ui->gotoX->setValue(ui->labelPosX->text().toDouble());
	if (ui->labelPosY->rect().contains(ui->labelPosY->mapFromGlobal(event->globalPos())))
		ui->gotoY->setValue(ui->labelPosY->text().toDouble());
	if (ui->labelPosZ->rect().contains(ui->labelPosZ->mapFromGlobal(event->globalPos())))
		ui->gotoZ->setValue(ui->labelPosZ->text().toDouble());
	if (ui->labelPosU->rect().contains(ui->labelPosU->mapFromGlobal(event->globalPos())))
		ui->gotoU->setValue(ui->labelPosU->text().toDouble());
	QWidget::mouseDoubleClickEvent(event);
}
// 
// void PlatformController::on_actionHomeZ_triggered()
// {
// 	smp86xHandler[0]->home(2);
// }
