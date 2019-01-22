#include "stdafx.h"
#include "arraydatasetup.h"
#include "ui_arraydatasetup.h"

extern double pulseEquivalent[];

ArrayDataSetup::ArrayDataSetup(QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::MSWindowsFixedSizeDialogHint)
{
	ui = new Ui::ArrayDataSetup();
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setEnabled(false);
	//setEnabled((tableWidget = qobject_cast<QTableWidget*>(parent)) != 0);

	ui->lineEdit->setValidator(new QDoubleValidator(-9999, 9999, 3, ui->lineEdit));
	ui->lineEdit_2->setValidator(new QDoubleValidator(-9999, 9999, 3, ui->lineEdit_2));

	ui->lineEdit->addAction(ui->actionGet);
	ui->lineEdit_2->addAction(ui->actionGet);
	ui->lineEdit_3->addAction(ui->actionGet_2);

	//ui->tableWidget->setItemDelegate(new MbItemDelegate);

	QAbstractSpinBox* spinBoxes[] = { ui->spinBox, ui->spinBox_2, ui->doubleSpinBox, ui->doubleSpinBox_2 };
	for (int i = 0; i < sizeof(spinBoxes) / sizeof(QAbstractSpinBox*); i++)
		connect(spinBoxes[i], SIGNAL(valueChanged(const QString &)), this, SLOT(slotUpdateTable()));
	connect(ui->lineEdit_3, SIGNAL(editingFinished()), this, SLOT(slotUpdateTable()));

	//if (tableWidget)
	//{
	//	currentRow = tableWidget->rowCount();
	//}
}

ArrayDataSetup::~ArrayDataSetup()
{
	delete ui;
}

void ArrayDataSetup::setTable(QTableWidget* table1, QTableWidget* table2)
{
	tableWidget = table1;
	tableWidget_2 = table2;
	setEnabled(true);
	if (tableWidget)
	{
		restRow = tableWidget->rowCount();
	}	
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

void ArrayDataSetup::on_actionGet_triggered()
{
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	QPointF p = /*orthoPos*/(QPointF(ss.axis_status[0].logicPos*pulseEquivalent[0], ss.axis_status[1].logicPos*pulseEquivalent[1]));
	//QPointF p = orthoPos(QPointF(getAxis(X).logicPos(), getAxis(Y).logicPos()));
	ui->lineEdit->setText(QString("%1").arg(p.x(), 0, 'f', 3));
	ui->lineEdit_2->setText(QString("%1").arg(p.y(), 0, 'f', 3));
}

void ArrayDataSetup::on_actionGet_2_triggered()
{
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	QPointF p2 = /*orthoPos*/(QPointF(ss.axis_status[0].logicPos*pulseEquivalent[0], ss.axis_status[1].logicPos*pulseEquivalent[1]));
	//QPointF p2 = orthoPos(QPointF(getAxis(X).logicPos(), -getAxis(Y).logicPos()));
	QPointF p1 = QPointF(ui->lineEdit->text().toDouble(), -ui->lineEdit_2->text().toDouble());
	ui->lineEdit_3->setText(QString("%1").arg(QLineF(p1, p2).angle(), 0, 'f', 3));
	slotUpdateTable();
}

void ArrayDataSetup::on_pushButton_clicked()
{
	if (QMessageBox::Ok == QMessageBox::information(this, QString::fromUtf16(L"注意"), QString::fromUtf16(L"请确定起始位置XY是否设置正确!"), QMessageBox::Ok | QMessageBox::Cancel))
	{
		tableWidget->setRowCount(restRow  + (ui->tableWidget->rowCount() - 1)*item_count);
		tableWidget_2->setRowCount(restRow + (ui->tableWidget->rowCount() - 1)*item_count);
		if (lastRow != restRow - 1)
		{
			for (int i = lastRow + 1; i <= restRow - 1; i++)
			{
				for (int k = 0; k < tableWidget->columnCount(); k++)
				{
					QTableWidgetItem* item = new QTableWidgetItem;
					item->setTextAlignment(Qt::AlignCenter);
					item->setText(tableWidget->item(i, k)->text());
					tableWidget->setItem(i + (ui->tableWidget->rowCount() - 1)*item_count, k, item);
				}
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count , 0)->setCheckState(tableWidget->item(i, 0)->checkState());
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 0)->setFlags(tableWidget->item(i, 0)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 3)->setFlags(tableWidget->item(i, 3)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 4)->setFlags(tableWidget->item(i, 4)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i + (ui->tableWidget->rowCount() - 1)*item_count, 6)->setCheckState(tableWidget->item(i, 6)->checkState());
			}
		}
			
		for (int i = 1; i < ui->tableWidget->rowCount(); i++)
		{
			for (int j = lastRow; j >= mylsit.at(0); j--)
			{
				for (int k = 0; k < tableWidget->columnCount(); k++)
				{
					QTableWidgetItem* item = new QTableWidgetItem;
					item->setTextAlignment(Qt::AlignCenter);
					item->setText(tableWidget->item(j, k)->text());
					tableWidget->setItem(i*item_count + j, k, item);
				}
				QTransform t = QTransform().translate(ui->tableWidget->item(i, 0)->text().toDouble(), ui->tableWidget->item(i, 1)->text().toDouble())
					.translate(ui->lineEdit->text().toDouble() + ui->doubleSpinBox->value() / 2, ui->lineEdit_2->text().toDouble() + ui->doubleSpinBox_2->value() / 2).rotate(ui->tableWidget->item(i, 2)->text().toDouble());
				double x = tableWidget->item(j, 1)->text().toDouble() - ui->lineEdit->text().toDouble() - ui->doubleSpinBox->value() / 2;
				double y = tableWidget->item(j, 2)->text().toDouble() - ui->lineEdit_2->text().toDouble() - ui->doubleSpinBox_2->value() / 2;
				float u = tableWidget->item(j, 5)->text().toDouble();
				t.map(x, y, &x, &y);
				tableWidget->item(i*item_count + j, 1)->setText(QString("%1").arg(x, 0, 'f', 3));
				tableWidget->item(i*item_count + j, 2)->setText(QString("%1").arg(y, 0, 'f', 3));
				tableWidget->item(i*item_count + j, 5)->setText(QString("%1").arg(u + ui->tableWidget->item(i, 2)->text().toDouble(), 0, 'f', 0));
				tableWidget->item(i*item_count + j, 0)->setCheckState(tableWidget->item(item_count-1, 0)->checkState());
				tableWidget->item(i*item_count + j, 0)->setFlags(tableWidget->item(i*item_count + j, 0)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i*item_count + j, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
				tableWidget->item(i*item_count + j, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
				tableWidget->item(i*item_count + j, 3)->setFlags(tableWidget->item(i*item_count + j, 3)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i*item_count + j, 4)->setFlags(tableWidget->item(i*item_count + j, 4)->flags()&(~Qt::ItemIsEditable));
				tableWidget->item(i*item_count + j, 6)->setCheckState(tableWidget->item(j, 6)->checkState());
			}
		}
	}
}

// void ArrayDataSetup::on_pushButton_2_clicked()
// {
// // 	if (tableWidget)
// // 	{
// // 		tableWidget->setRowCount(currentRow);
// // 	}
// // 	if (tableWidget_2)
// // 	{
// // 		tableWidget_2->setRowCount(currentRow);
// // 	}
// }

void ArrayDataSetup::on_pushButton_3_clicked()
{
	close();
}

void ArrayDataSetup::slotUpdateTable()
{
	int rowCount = ui->tableWidget->rowCount();
	int newRowCount = ui->spinBox->value()*ui->spinBox_2->value();
	ui->tableWidget->setRowCount(newRowCount);
	for (int i = rowCount; i < newRowCount; i++)
	{
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem("0"));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem("0"));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem("0"));
		ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
		ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);
	}
	for (int i = 0; i < ui->spinBox_2->value(); i++)
	{
		for (int j = 0; j < ui->spinBox->value(); j++)
		{
			QTransform t = QTransform().rotate(ui->lineEdit_3->text().toDouble()).translate(j*ui->doubleSpinBox->value(), i*ui->doubleSpinBox_2->value());
			QPointF p = t.map(QPointF());
			ui->tableWidget->item(i*ui->spinBox->value() + j, 0)->setText(QString("%1").arg(p.x(), 0, 'f', 3));
			ui->tableWidget->item(i*ui->spinBox->value() + j, 1)->setText(QString("%1").arg(p.y(), 0, 'f', 3));
			//ui->tableWidget->item(i*ui->spinBox->value()+j, 0)->setText(QString("%1").arg(j*ui->doubleSpinBox->value(), 0, 'f', 3));
			//ui->tableWidget->item(i*ui->spinBox->value()+j, 1)->setText(QString("%1").arg(i*ui->doubleSpinBox_2->value(), 0, 'f', 3));
		}
	}

}

