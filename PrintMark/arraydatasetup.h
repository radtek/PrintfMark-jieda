#ifndef ARRAYDATASETUP_H
#define ARRAYDATASETUP_H

#include <QWidget>
namespace Ui {class ArrayDataSetup;};

class ArrayDataSetup : public QWidget
{
	Q_OBJECT

public:
	ArrayDataSetup(QWidget *parent = 0);
	~ArrayDataSetup();

	void setTable(QTableWidget* table1, QTableWidget* table2);
	void setHandler(Smp86xHandler* smp86xHandler){
		this->smp86xHandler = smp86xHandler;
	}

protected slots:
	void on_actionGet_triggered();
	void on_actionGet_2_triggered();
	void on_pushButton_clicked();
/*	void on_pushButton_2_clicked();*/
	void on_pushButton_3_clicked();
	void slotUpdateTable();
private:
	Ui::ArrayDataSetup *ui;
	Smp86xHandler* smp86xHandler;
	QTableWidget* tableWidget;
	QTableWidget* tableWidget_2;
	QList<int> mylsit;
	QList<QTableWidgetSelectionRange> ranges;
	int currentRow,restRow=0;
	int lastRow;
	int count = 0;
	int item_count = 0;
};

#endif // ARRAYDATASETUP_H
