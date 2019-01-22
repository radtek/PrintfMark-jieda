#include "stdafx.h"
#include "ink.h"
#include <qtimer.h>
#include <QListWidgetItem>
#include <cmath>
#include "Help.h"
#include "MKU6000.h"
using namespace std;

ink::ink(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QSettings settings;
	QString temp;
	
	QCheckBox* checkbox[36] = { ui.checkBox,ui.checkBox_2,ui.checkBox_3,ui.checkBox_4,ui.checkBox_5
		,ui.checkBox_6,ui.checkBox_7,ui.checkBox_8,ui.checkBox_9,ui.checkBox_10
		,ui.checkBox_11,ui.checkBox_12,ui.checkBox_13,ui.checkBox_14,ui.checkBox_15,ui.checkBox_16
		,ui.checkBox_17,ui.checkBox_18,ui.checkBox_19,ui.checkBox_20,ui.checkBox_21,ui.checkBox_22
		,ui.checkBox_23,ui.checkBox_24,ui.checkBox_25,ui.checkBox_26,ui.checkBox_27,ui.checkBox_28
		,ui.checkBox_29,ui.checkBox_30,ui.checkBox_31,ui.checkBox_32,ui.checkBox_33,ui.checkBox_34,ui.checkBox_35,ui.checkBox_36
	};
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
		{
			temp = settings.value(QString("ink_printf%1/countcode").arg(i), "0123456789").toString();
		}
	}
	for (int i = 0; i<36; i++)
	{
		if (temp.contains(checkbox[i]->text(),Qt::CaseInsensitive))
		{
			checkbox[i]->setChecked(true);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		num[i] = settings.value(QString("ink_printf%1/text_number").arg(i), 0).toInt();
		if (num[i] != 0)
		{
			for (int j = 0; j < num[i]; j++)
			{
				QString asdv = settings.value(QString("ink_printf%1/text%2").arg(i).arg(j), NULL).toString();
				(*listWidgets[i])->addItem(asdv);
				if (settings.value(QString("ink_printf%1/text%2").arg(i).arg(j), NULL).toString().startsWith("N"))
					numb[i] = settings.value(QString("ink_printf%1/text%2").arg(i).arg(j), NULL).toString().remove(0,2);
			}
		}
	}
	on_pushButton_5_clicked();
	ui.lineEdit_6->setText(temp);
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()),SLOT(updata_currentdata()));
	timer->start(500);
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(deleteitem()));
	connect(ui.tabWidget_4, SIGNAL(currentChanged(int)),this,SLOT(changupcode()));
	connect(ui.spinBox, SIGNAL(valueChanged(int)),this,SLOT(changespinbox()));
	QRegExp rx("[A-F0-9]{16}$");
	QRegExp rx1("[A-Z0-9]*$");
	QRegExpValidator *validator = new QRegExpValidator(rx, this);
	QRegExpValidator *validator1 = new QRegExpValidator(rx1, this);
	//ui.lineEdit_4->setValidator(validator);
	ui.lineEdit_5->setValidator(validator1);
}

void ink::updata_currentdata()
{
	QString updata = NULL;
	ui.dateTimeEdit->setDateTime(QDateTime::currentDateTime());
	if (ui.radioButton->isChecked())
	{
		QString data = QDateTime::currentDateTime().toString("MM.dd");
		ui.radioButton->setText( data );
		QRegExp rx("\\.");
		int pos = 0;
		while ((pos = rx.indexIn(data, pos)) != -1)
		{
			data = data.remove(pos, 1);
			pos = rx.matchedLength();
		}
		ui.lineEdit_2->setText(data);
	}
	if (ui.radioButton_2->isChecked())
	{
		QString data = QDateTime::currentDateTime().toString("yyyy.MM.dd");
		ui.radioButton_2->setText(data);
		QRegExp rx("\\.");
		int pos = 0;
		while ((pos = rx.indexIn(data, pos)) != -1)
		{
			data = data.remove(pos, 1);
			pos = rx.matchedLength();
		}
		ui.lineEdit_2->setText(data);
	}
	if (ui.radioButton_3->isChecked())
	{
		QString data = QDateTime::currentDateTime().toString("yy.MM.dd");
		ui.radioButton_3->setText(data);
		QRegExp rx("\\.");
		int pos = 0;
		while ((pos = rx.indexIn(data, pos)) != -1)
		{
			data = data.remove(pos, 1);
			pos = rx.matchedLength();
		}
		ui.lineEdit_2->setText(data);
	}
	ui.lineEdit_5->setMaxLength(ui.spinBox->value());
	QCheckBox* checkbox[36] = { ui.checkBox,ui.checkBox_2,ui.checkBox_3,ui.checkBox_4,ui.checkBox_5
		,ui.checkBox_6,ui.checkBox_7,ui.checkBox_8,ui.checkBox_9,ui.checkBox_10
		,ui.checkBox_11,ui.checkBox_12,ui.checkBox_13,ui.checkBox_14,ui.checkBox_15,ui.checkBox_16
		,ui.checkBox_17,ui.checkBox_18,ui.checkBox_19,ui.checkBox_20,ui.checkBox_21,ui.checkBox_22
		,ui.checkBox_23,ui.checkBox_24,ui.checkBox_25,ui.checkBox_26,ui.checkBox_27,ui.checkBox_28
		,ui.checkBox_29,ui.checkBox_30,ui.checkBox_31,ui.checkBox_32,ui.checkBox_33,ui.checkBox_34,ui.checkBox_35,ui.checkBox_36
	};
	for (int i =0;i<36;i++)
	{
		if (checkbox[i]->isChecked())
			updata.append(checkbox[i]->text());
	}
	ui.lineEdit_6->setText(updata);
}

void ink::on_pushButton_clicked()
{
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
			(*listWidgets[i])->addItem(QString("M ").append(ui.lineEdit->text()));
	}
}

void ink::on_pushButton_2_clicked()
{
	QSettings settings;
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
			(*listWidgets[i])->addItem(QString("N ").append(ui.lineEdit_5->text()));
	}	
}

void ink::on_pushButton_3_clicked()
{
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
			(*listWidgets[i])->addItem(QString("T ").append(ui.lineEdit_2->text()));
	}
}

void ink::on_pushButton_5_clicked() 
{
	QString ink_data = NULL;
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
		{
			if ((*listWidgets[i])->count() != 0)
			{
				for (int j = 0; j < (*listWidgets[i])->count(); j++)
				{
					QString s = (*listWidgets[i])->item(j)->text();
					ink_data = ink_data.append(s.remove(0, 2));
				}
			}
		}
	}
	ui.lineEdit_3->setText(ink_data);
}

 void ink::on_pushButton_6_clicked()
 {
	 for (int i = 0; i < 5; i++)
	 {
		 if (ui.tabWidget_4->currentIndex() == i)
		 {
			 QSettings settings;
			 settings.setValue(QString("ink_printf%1/Step").arg(i), ui.spinBox_2->text());
		 }
	 }
 }

void ink::on_pushButton_7_clicked()
{
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
		{
			QSettings settings;
			settings.setValue(QString("ink_printf%1/countcode").arg(i), ui.lineEdit_6->text());
		}
	}
	
}

// void ink::on_pushButton_8_clicked()
// {
// 	Help he(this);
// 	if (QDialog::Accepted == he.exec())
// 	{
// 	}
// }

// void ink::on_pushButton_9_clicked()
// {
// 	QSettings settings;
// 	settings.setValue("ink_printf/mku6000",ui.lineEdit_7->text());
// }

// void ink::on_pushButton_10_clicked()
// {
// 	MKU6000 mk(this);
// 	if (QDialog::Accepted == mk.exec())
// 	{
// 	}
// }

void ink::deleteitem()
{
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
			(*listWidgets[i])->takeItem((*listWidgets[i])->currentRow());
	}
	/*ui.listWidget->takeItem(ui.listWidget->currentRow());*/
}

void ink::changupcode()
{
	QSettings settings;
	QString temp;
	QCheckBox* checkbox[36] = { ui.checkBox,ui.checkBox_2,ui.checkBox_3,ui.checkBox_4,ui.checkBox_5
		,ui.checkBox_6,ui.checkBox_7,ui.checkBox_8,ui.checkBox_9,ui.checkBox_10
		,ui.checkBox_11,ui.checkBox_12,ui.checkBox_13,ui.checkBox_14,ui.checkBox_15,ui.checkBox_16
		,ui.checkBox_17,ui.checkBox_18,ui.checkBox_19,ui.checkBox_20,ui.checkBox_21,ui.checkBox_22
		,ui.checkBox_23,ui.checkBox_24,ui.checkBox_25,ui.checkBox_26,ui.checkBox_27,ui.checkBox_28
		,ui.checkBox_29,ui.checkBox_30,ui.checkBox_31,ui.checkBox_32,ui.checkBox_33,ui.checkBox_34,ui.checkBox_35,ui.checkBox_36
	};
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
		{
			temp = settings.value(QString("ink_printf%1/countcode").arg(i), "0123456789").toString();
		}
	}
	for (int i = 0; i < 36; i++)
	{
		if (temp.contains(checkbox[i]->text(), Qt::CaseInsensitive))
		{
			checkbox[i]->setChecked(true);
		}
	}
}

void ink::changespinbox()
{
	QSettings settings;
	settings.setValue(QString("ink_printf%1/codenum").arg(ui.tabWidget_4->currentIndex()), ui.spinBox->value());
}

void ink::accept()
{
	QSettings settings;
	for (int i = 0; i < 5; i++)
	{
		if (ui.tabWidget_4->currentIndex() == i)
		{
			settings.setValue(QString("ink_printf%1/text_number").arg(i), (*listWidgets[i])->count());
			for (int j = 0; j < (*listWidgets[i])->count(); j++)
			{
				settings.setValue(QString("ink_printf%1/text%2").arg(i).arg(j), (*listWidgets[i])->item(j)->text());
				if ((*listWidgets[i])->item(j)->text().startsWith("N"))
				{
					if (numb != (*listWidgets[i])->item(j)->text())
						settings.setValue(QString("ink_printf%1/first").arg(i), (*listWidgets[i])->item(j)->text());
				}
			}
		}
	}
	QDialog::accept();
}


ink::~ink()
{
}





