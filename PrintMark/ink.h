#pragma once

#include <QDialog>
#include "ui_ink.h"

class ink : public QDialog
{
	Q_OBJECT

public:
	ink(QWidget *parent = Q_NULLPTR);
	~ink();

private:
	Ui::ink ui;
	void accept();
	int num[5];
	QString numb[5];
	QListWidget** listWidgets[5] = { &ui.listWidget, &ui.listWidget_2 ,&ui.listWidget_3,&ui.listWidget_4,&ui.listWidget_5 };

protected slots:
	void updata_currentdata();
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	/*void on_pushButton_8_clicked();*/
	//void on_pushButton_9_clicked();
	//void on_pushButton_10_clicked();
	void deleteitem();
	void changupcode();
	void changespinbox();
};
