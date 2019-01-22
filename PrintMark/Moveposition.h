#pragma once

#include <QWidget>
#include "ui_Moveposition.h"

class Moveposition : public QWidget
{
	Q_OBJECT

public:
	Moveposition(QWidget *parent = Q_NULLPTR);
	void setTable(QTableWidget* table1);
	~Moveposition();

	protected slots:
	void on_pushButton_clicked();

private:
	Ui::Moveposition ui;
	QTableWidget* tableWidget;
	QList<int> mylsit;
	QList<QTableWidgetSelectionRange> ranges;
	int count, item_count;
	int lastRow;
};
