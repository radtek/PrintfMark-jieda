#include "stdafx.h"
#include "iomonitor.h"
#include "ui_iomonitor.h"

IoMonitor::IoMonitor(Smp86xHandler* _smp86xHandler, QWidget *parent )
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint|Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint/*|Qt::WindowTitleHint|Qt::WindowMinimizeButtonHint|Qt::WindowSystemMenuHint*/)
	, ui(new Ui::IoMonitor)
	, smp86xHandler(_smp86xHandler)
{
	ui->setupUi(this);
	ui->buttonBox->hide();
	QToolButton* buttons[] = {
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11,   
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27, 
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	QWidget* w[] = {
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27, 
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
		ui->di16, ui->di17, ui->di18, ui->di19, ui->di20, ui->di21, ui->di22, 
		ui->di23, ui->di24, ui->di25, ui->di26, ui->di27, ui->di28, ui->di29, 
		ui->di30, ui->di31, ui->label_52, ui->label_53, ui->label_54, ui->label_55, 
		ui->label_56, ui->label_57, ui->label_58, ui->label_59, ui->label_60, 
		ui->label_61, ui->label_62, ui->label_63, ui->label_64, ui->label_65, 
		ui->label_66, ui->label_67, 
	};
// #ifdef _OLD_VERSION
// 	for(int i=0; i<(sizeof(w)/sizeof(QWidget*)); i++)
// 		w[i]->hide();
// #endif // _OLD_VERSION

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), SLOT(slotTimeout()));
	timer->start(50);

	setLabels(QApplication::applicationDirPath() + "/iolabels.ini");
}

IoMonitor::~IoMonitor()
{
	//QSettings settings;
	//settings.setValue("IoMonitor/geometry", saveGeometry());
	delete ui;
}

void IoMonitor::on_buttonGroup_buttonClicked( QAbstractButton * button )
{
	if (!ui->checkBox->isChecked())
	{
		QToolButton* buttons[] = {
			ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
			ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
			ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11,   
			ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
			ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
			ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
			ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27,
			ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
		};

		for (int i=0; i<(sizeof(buttons)/sizeof(QToolButton*)); i++)
		{
			if(buttons[i] != button)
				continue;

			//Smp86x::setOutput(slave, i, !button->isChecked());
			smp86xHandler->setOutput(i, !button->isChecked());
			break;
		}
	}
}

void IoMonitor::on_buttonGroup_buttonPressed( QAbstractButton * button )
{
	QToolButton* buttons[] = {
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11,   
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27, 
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	for (int i=0; i<(sizeof(buttons)/sizeof(QToolButton*)); i++)
	{
		if(buttons[i] != button)
			continue;

		if (ui->checkBox->isChecked())
			smp86xHandler->setOutput(i, 0);
			//Smp86x::setOutput(slave, i, 0);

		break;
	}
}

void IoMonitor::on_buttonGroup_buttonReleased( QAbstractButton * button )
{
	QToolButton* buttons[] = {
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11,   
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27, 
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	for (int i=0; i<(sizeof(buttons)/sizeof(QToolButton*)); i++)
	{
		if(buttons[i] != button)
			continue;

		if (ui->checkBox->isChecked())
			smp86xHandler->setOutput(i, 1);
			//Smp86x::setOutput(slave, i, 1);

		break;
	}
}

void IoMonitor::on_checkBox_clicked( bool checked )
{
	QToolButton* buttons[] = {
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11, 
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27,
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	for (int i=0; i<(sizeof(buttons)/sizeof(QToolButton*)); i++)
		buttons[i]->setCheckable(!checked);
}

void IoMonitor::slotTimeout()
{
	if(!isVisible())
		return;

	static char sheetGreen[] = "color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #76f77a, stop: 1 #6adb6e);";
	static char sheetRed[] = "color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ea353a, stop:1 #fa464a);";

	QLabel* const slmtp[] = {ui->slmtp0, ui->slmtp1, ui->slmtp2, ui->slmtp3};
	QLabel* const slmtm[] = {ui->slmtm0, ui->slmtm1, ui->slmtm2, ui->slmtm3};
	QLabel* const elp[] = {ui->elp0, ui->elp1, ui->elp2, ui->elp3};
	QLabel* const elm[] = {ui->elm0, ui->elm1, ui->elm2, ui->elm3};
	QLabel* const emg[] = {ui->emg0, ui->emg1, ui->emg2, ui->emg3};
	QLabel* const index[] = {ui->index0, ui->index1, ui->index2, ui->index3};
	QLabel* const org[] = {ui->org0, ui->org1, ui->org2, ui->org3};
	QLabel* const pa[] = {ui->pa0, ui->pa1, ui->pa2, ui->pa3};
	QLabel* const pb[] = {ui->pb0, ui->pb1, ui->pb2, ui->pb3};
	QLabel* const inp[] = {ui->inp0, ui->inp1, ui->inp2, ui->inp3};
	QLabel* const alm[] = {ui->alm0, ui->alm1, ui->alm2, ui->alm3};
	QLabel* const dip[] = {ui->di0, ui->di1, ui->di2, ui->di3, ui->di4, ui->di5, ui->di6, ui->di7,
		ui->di8, ui->di9, ui->di10, ui->di11, ui->di12, ui->di13, ui->di14,
		ui->di15, ui->di16, ui->di17, ui->di18, ui->di19, ui->di20,
		ui->di21, ui->di22, ui->di23, ui->di24, ui->di25, ui->di26, ui->di27,
		ui->di28, ui->di29, ui->di30, ui->di31,
	};
	//QLabel* const dop[] = {ui->do0, ui->do1, ui->do2, ui->do3, ui->do4, ui->do5, ui->do6, ui->do7,
	//	ui->do8, ui->do9, ui->do10, ui->do11, ui->do12, ui->do13, ui->do14, ui->do15};

	QToolButton* buttons[] = {
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3, 
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7, 
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11, 
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15, 
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19, 
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23, 
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27,
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	setUpdatesEnabled(false);
	uchar status[4] = {0,};

	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();

	for(int i=0; i<4; i++)
	{
		status[i] = ss.axis_status[i].state >> 8;
		slmtp[i]->setStyleSheet((status[i] & 0x80) ? sheetRed : sheetGreen);
		slmtm[i]->setStyleSheet((status[i] & 0x40) ? sheetRed : sheetGreen);
		elp[i]->setStyleSheet((status[i] & 0x20) ? sheetRed : sheetGreen);
		elm[i]->setStyleSheet((status[i] & 0x10) ? sheetRed : sheetGreen);
		emg[i]->setStyleSheet((status[i] & 0x8) ? sheetRed : sheetGreen);
		index[i]->setStyleSheet((status[i] & 0x4) ? sheetRed : sheetGreen);
		org[i]->setStyleSheet((status[i] & 0x2) ? sheetRed : sheetGreen);
		pa[i]->setStyleSheet((status[i] & 0x1) ? sheetRed : sheetGreen);
		//pb[i]->setStyleSheet((status & 0x800) ? sheetRed : sheetGreen);
		//inp[i]->setStyleSheet((status & 0x1000) ? sheetRed : sheetGreen);
		//alm[i]->setStyleSheet((status & 0x100000) ? sheetRed : sheetGreen);
	}

	for (int i=0; i<(sizeof(dip)/sizeof(QLabel*)); i++)
	{
		dip[i]->setStyleSheet(ss.inputs&(0x1<<i) ? sheetGreen : sheetRed);
	}

	setUpdatesEnabled(true);	
}

void IoMonitor::setLabels(const QString& labelFile)
{
	QLabel* l[] = {
		ui->label_22, ui->label_23, ui->label_24, ui->label_25, ui->label_26, ui->label_27, ui->label_29, ui->label_28,
		ui->label_50, ui->label_49, ui->label_48, ui->label_47, ui->label_46, ui->label_45, ui->label_44, ui->label_43,
		ui->label_52, ui->label_53, ui->label_54, ui->label_55, ui->label_56, ui->label_57, ui->label_58, ui->label_59,
		ui->label_60, ui->label_61, ui->label_62, ui->label_63, ui->label_64, ui->label_65, ui->label_66, ui->label_67,
	};

	QToolButton* buttons[] = { 
		ui->toolButton0, ui->toolButton1, ui->toolButton2, ui->toolButton3,
		ui->toolButton4, ui->toolButton5, ui->toolButton6, ui->toolButton7,
		ui->toolButton8, ui->toolButton9, ui->toolButton10, ui->toolButton11,
		ui->toolButton12, ui->toolButton13, ui->toolButton14, ui->toolButton15,
		ui->toolButton16, ui->toolButton17, ui->toolButton18, ui->toolButton19,
		ui->toolButton20, ui->toolButton21, ui->toolButton22, ui->toolButton23,
		ui->toolButton24, ui->toolButton25, ui->toolButton26, ui->toolButton27, 
		ui->toolButton28, ui->toolButton29, ui->toolButton30, ui->toolButton31,
	};

	QSettings settings(labelFile, QSettings::IniFormat);
	settings.setIniCodec("gbk");
	for (int i = 0; i < (sizeof(l) / sizeof(QLabel*)); i++)
	{
		l[i]->setText(/*QString::fromLocal8Bit*/(settings.value(QString("Labels/Di%1").arg(i + 1), i + 1).toString()));
	}
	for (int i = 0; i < (sizeof(buttons) / sizeof(QToolButton*)); i++)
	{
		buttons[i]->setText(/*QString::fromLocal8Bit*/(settings.value(QString("Labels/Do%1").arg(i + 1), i + 1).toString()));
	}
}

