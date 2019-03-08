#include "stdafx.h"
#include "Moveposition.h"

Moveposition::Moveposition(QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::MSWindowsFixedSizeDialogHint)
{
	ui.setupUi(this);
	ui.lineEdit_3->setText("0");
	ui.lineEdit->setText("0");
	ui.lineEdit_2->setText("0");
	QRegExp rx1("[+-]?[0-9]*\.?[0-9]*$");
	QRegExpValidator *validator1 = new QRegExpValidator(rx1, this);
	ui.lineEdit->setValidator(validator1);
	ui.lineEdit_2->setValidator(validator1);
	ui.lineEdit_3->setValidator(validator1);
}

void Moveposition::setTable(QTableWidget * table1)
{
	tableWidget = table1;
	setEnabled(true);
	ranges = tableWidget->selectedRanges();
	count = ranges.count();
	for (int i = 0; i < count; i++)
	{
		int topRow = ranges.at(i).topRow();
		int bottomRow = ranges.at(i).bottomRow();
		for (int j = bottomRow; j >= topRow; j--)
		{
			mylsit.push_back(j);
		}
	}
	qSort(mylsit.begin(), mylsit.end());
	item_count = mylsit.size();
	lastRow = mylsit.at(mylsit.size() - 1);
}

void Moveposition::on_pushButton_clicked()
{
	if (QMessageBox::Ok == QMessageBox::information(this, QString::fromUtf16(L"注意"), QString::fromUtf16(L"确定所选点进行偏移？"), QMessageBox::Ok | QMessageBox::Cancel))
	{
		for (int i = 0; i < item_count; i++)
		{
			double x = tableWidget->item(mylsit[i], 1)->text().toDouble() + ui.lineEdit->text().toDouble();
			double y = tableWidget->item(mylsit[i], 2)->text().toDouble() + ui.lineEdit_2->text().toDouble();
			float u = tableWidget->item(mylsit[i], 5)->text().toDouble() + ui.lineEdit_3->text().toDouble();
			tableWidget->item(mylsit[i], 1)->setText(QString("%1").arg(x, 0, 'f', 3));
			tableWidget->item(mylsit[i], 2)->setText(QString("%1").arg(y, 0, 'f', 3));
			tableWidget->item(mylsit[i], 5)->setText(QString("%1").arg(u, 0, 'f', 0));
		}
	}
}

Moveposition::~Moveposition()
{
}
