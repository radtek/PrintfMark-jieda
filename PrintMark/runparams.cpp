#include "stdafx.h"
#include "runparams.h"
#include "ui_runparams.h"

extern int speedValue[];
extern int chushi;

RunParams::RunParams(Smp86xHandler* sh, QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::RunParams())
	, smp86xHandler(sh)
{
	ui->setupUi(this);
	ui->groupBox_10->hide();
	setAttribute(Qt::WA_DeleteOnClose);
#ifdef FoxlinkAdd
	ui->label_46->setText(QString::fromUtf16(L"機臺編號"));
#endif // FoxlinkAdd


	QSettings settings;
	QSpinBox* spinBoxes[] = {
		ui->spinBox,      ui->spinBox_2,    ui->spinBox_3, 
		ui->spinBox_4,    ui->spinBox_5,	ui->spinBox_6, 
		ui->spinBox_7,    ui->spinBox_8,    ui->spinBox_9, 
		ui->spinBox_10,   ui->spinBox_11,   ui->spinBox_12,
		ui->spinBox_13,   ui->spinBox_14,   ui->spinBox_15, 
	};
	for (int i=0; i<((sizeof(spinBoxes)/sizeof(QSpinBox*))); i++)
	{
		spinBoxes[i]->setValue(settings.value(QString("Speed/v%1").arg(i)).toInt());
	}

	ui->lineEdit->setText(settings.value("Print/dist", 10000).toString());
	ui->lineEdit->setValidator(new QIntValidator(ui->lineEdit));
	ui->doubleSpinBox->setValue(settings.value("Print/angle", 0).toDouble());
	ui->lineEdit_6->setText(settings.value("Print/z", 0).toString());
	ui->lineEdit_7->setText(settings.value("Print/u", 0).toString());
	ui->spinBox_16->setValue(settings.value("Print/delay", 100).toInt());
	ui->spinBox_17->setValue(settings.value("Print/speed", 100).toInt());
	ui->doubleSpinBox_2->setValue(settings.value("Print/division", 40).toDouble());

	ui->groupBox_3->setChecked(settings.value("Code/enable", true).toBool());
	//ui->lineEdit_2->setText(settings.value("Code/prefix", "F0P54S").toString());
	//ui->lineEdit_3->setText(settings.value("Code/next", "0001").toString());
	//ui->lineEdit_4->setText(settings.value("Code/subfix", "FY9Y9Z1").toString());
	ui->lineEdit_14->setText(settings.value("Code/total", "0").toString());
	ui->lineEdit_17->setText(settings.value("Code/from", "1").toString());
	//ui->lineEdit_15->setText(settings.value("Code/first", "0001").toString());
	//ui->lineEdit_16->setText(settings.value("Code/last", "0001").toString());
	//ui->checkBox->setChecked(settings.value("Code/auto_reset", true).toBool());

	ui->lineEdit_8 ->setText(settings.value("Position/mark1_x", 0).toString());
	ui->lineEdit_9 ->setText(settings.value("Position/mark1_y", 0).toString());
	ui->lineEdit_10->setText(settings.value("Position/mark1_z", 0).toString());
	ui->lineEdit_11->setText(settings.value("Position/mark2_x", 0).toString());
	ui->lineEdit_12->setText(settings.value("Position/mark2_y", 0).toString());
	ui->lineEdit_13->setText(settings.value("Position/mark2_z", 0).toString());

	ui->spinBox_18->setValue(settings.value("Delay/mark", 100).toInt());
	ui->spinBox_19->setValue(settings.value("Delay/badm", 100).toInt());
	ui->spinBox_20->setValue(settings.value("Delay/code", 100).toInt());

	ui->spinBox_21->setValue(settings.value("Light/mark", 30).toInt());
	ui->spinBox_22->setValue(settings.value("Light/badm", 30).toInt());
	ui->spinBox_23->setValue(settings.value("Light/code", 30).toInt());

	ui->spinBox_24->setValue(settings.value("Delay/outlet", 100).toInt());

	ui->groupBox_7->setChecked(settings.value("BadMark/enabled", false).toBool());
	ui->lineEdit_5->setText(QString::fromLocal8Bit(settings.value("BadMark/path").toByteArray()));
	ui->lineEdit_24->setText(QString::fromLocal8Bit(settings.value("TimeRecord/path").toByteArray()));

	ui->lineEdit_18 ->setText(settings.value("Position/makeup_x", 0).toString());
	ui->lineEdit_19 ->setText(settings.value("Position/makeup_y", 0).toString());

	QIntValidator *validator = new QIntValidator(0, 999999, this);
	ui->lineEdit_14->setValidator(validator);
	ui->lineEdit_17->setValidator(new QIntValidator(0,999999,ui->lineEdit_17));
#ifdef _FOXLINK
	//ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0123456789ABCDEFGHJKLMNPQRSTUVWXYZ]{6}"), ui->lineEdit_2));
	//ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("[0123456789ABCDEFGHJKLMNPQRSTUVWXYZ]{4}"), ui->lineEdit_3));
	//ui->lineEdit_4->setValidator(new QRegExpValidator(QRegExp("[0123456789ABCDEFGHJKLMNPQRSTUVWXYZ]{7}"), ui->lineEdit_4));
#endif // _FOXLINK

	ui->lineEdit_20 ->setText(settings.value("SFC/endpoint").toString());
	ui->lineEdit_21 ->setText(settings.value("SFC/linename").toString());
	ui->comboBox->setCurrentIndex(settings.value("SFC/mode", 1).toInt());

}

RunParams::~RunParams()
{
	delete ui;
}

void RunParams::on_buttonBox_clicked( QAbstractButton * button )
{
	if (QDialogButtonBox::ApplyRole == ui->buttonBox->buttonRole(button))
	{
#ifdef _FOXLINK
		//if(ui->lineEdit_2->text().length() != 6)
		//{
		//	QMessageBox::information(this, QString::fromUtf16(L"错误"), QString::fromUtf16(L"二维码首段长度不等于6, 请检查!"));
		//	return;
		//}
		//if(ui->lineEdit_3->text().length() != 4)
		//{
		//	QMessageBox::information(this, QString::fromUtf16(L"错误"), QString::fromUtf16(L"二维码中段长度不等于4, 请检查!"));
		//	return;
		//}
		//if(ui->lineEdit_4->text().length() != 7)
		//{
		//	QMessageBox::information(this, QString::fromUtf16(L"错误"), QString::fromUtf16(L"二维码尾段长度不等于7, 请检查!"));
		//	return;
		//}
#endif // _FOXLINK
		QSettings settings;
		//QSpinBox* spinBox     = qobject_cast<QSpinBox*>(sender());
		QSpinBox* spinBoxes[] = {
			ui->spinBox,      ui->spinBox_2,     ui->spinBox_3, 
			ui->spinBox_4,    ui->spinBox_5,     ui->spinBox_6, 
			ui->spinBox_7,    ui->spinBox_8,     ui->spinBox_9, 
			ui->spinBox_10,   ui->spinBox_11,    ui->spinBox_12,
			ui->spinBox_13,   ui->spinBox_14,    ui->spinBox_15, 
		};
		for (int i=0; i<((sizeof(spinBoxes)/sizeof(QSpinBox*))); i++)
		{
			settings.setValue(QString("Speed/v%1").arg(i), spinBoxes[i]->value());
			speedValue[i] = spinBoxes[i]->value();
			//if (spinBoxes[i] == spinBox)
			//{
			//	value /= 50;
			//	smp86xHandler->writeRawData(0x26+i*2, 2, (ushort*)&value);
			//	break;
			//}
		}
		settings.setValue("Print/dist", ui->lineEdit->text().toInt());
		settings.setValue("Print/angle", ui->doubleSpinBox->value());
		settings.setValue("Print/z", ui->lineEdit_6->text().toDouble());
		settings.setValue("Print/u", ui->lineEdit_7->text().toDouble());
		settings.setValue("Print/delay", ui->spinBox_16->value());
		settings.setValue("Print/division", ui->doubleSpinBox_2->value());
		settings.setValue("Print/speed", ui->spinBox_17->value());

		settings.setValue("Code/enable", ui->groupBox_3->isChecked());
		//settings.setValue("Code/prefix", ui->lineEdit_2->text());
		//settings.setValue("Code/next", ui->lineEdit_3->text());
		//settings.setValue("Code/subfix", ui->lineEdit_4->text());
		settings.setValue("Code/total", ui->lineEdit_14->text().toInt());
		settings.setValue("Code/from", ui->lineEdit_17->text());
		//settings.setValue("Code/first", ui->lineEdit_15->text());
		//settings.setValue("Code/last", ui->lineEdit_16->text());
//		settings.setValue("Code/auto_reset", ui->checkBox->isChecked());

		settings.setValue("Position/mark1_x", ui->lineEdit_8 ->text());
		settings.setValue("Position/mark1_y", ui->lineEdit_9 ->text());
		settings.setValue("Position/mark1_z", ui->lineEdit_10->text());
		settings.setValue("Position/mark2_x", ui->lineEdit_11->text());
		settings.setValue("Position/mark2_y", ui->lineEdit_12->text());
		settings.setValue("Position/mark2_z", ui->lineEdit_13->text());

		settings.setValue("Delay/mark", ui->spinBox_18->value());
		settings.setValue("Delay/badm", ui->spinBox_19->value());
		settings.setValue("Delay/code", ui->spinBox_20->value());

		settings.setValue("BadMark/enabled", ui->groupBox_7->isChecked());
		settings.setValue("BadMark/path", ui->lineEdit_5->text().toLocal8Bit());
		settings.setValue("TimeRecord/path", ui->lineEdit_24->text().toLocal8Bit());

		settings.setValue("Light/mark", ui->spinBox_21->value());
		settings.setValue("Light/badm", ui->spinBox_22->value());
		settings.setValue("Light/code", ui->spinBox_23->value());

		settings.setValue("Delay/outlet", ui->spinBox_24->value());

		settings.setValue("Position/makeup_x", ui->lineEdit_18 ->text());
		settings.setValue("Position/makeup_y", ui->lineEdit_19 ->text());

		settings.setValue("SFC/endpoint", ui->lineEdit_20 ->text());
		settings.setValue("SFC/linename", ui->lineEdit_21 ->text());
		settings.setValue("SFC/mode", ui->comboBox->currentIndex());

		chushi = 1;
		emit paramsChanged();
	}
	if (QDialogButtonBox::RejectRole == ui->buttonBox->buttonRole(button))
		close();
	if (QDialogButtonBox::AcceptRole == ui->buttonBox->buttonRole(button))
		close();
}

void RunParams::on_pushButton_clicked()
{
	QAction* action = QMenu::exec(QList<QAction*>() << ui->actionGetPos << ui->actionGotoXY << ui->actionGotoZ, QCursor::pos());
	if (action == ui->actionGetPos)
	{ 
		QSettings settings;
		SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
		double pulseEquivalent0 = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
		double pulseEquivalent1 = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
		double pulseEquivalent2 = settings.value(QString("PulseEquivalent0/2"), 0.01).toDouble();
		ui->lineEdit_8-> setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent0, 0, 'f', 3));
		ui->lineEdit_9-> setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent1, 0, 'f', 3));
		ui->lineEdit_10->setText(QString("%1").arg(ss.axis_status[2].logicPos*pulseEquivalent2, 0, 'f', 3));
	}
	if (action == ui->actionGotoXY)
	{
		QSettings settings;
		SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
		double pulseEquivalent0 = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
		double pulseEquivalent1 = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
		double x = ui->lineEdit_8->text().toDouble();
		double y = ui->lineEdit_9->text().toDouble();
		smp86xHandler->start(0, 1, (x/pulseEquivalent0 - ss.axis_status[0].logicPos), (y/pulseEquivalent1 - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
	//if (action == ui->actionGotoZ)
	//{
	//	QSettings settings;
	//	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	//	double pulseEquivalent2 = settings.value(QString("PulseEquivalent0/2"), 0.01).toDouble();
	//	double z = ui->lineEdit_10->text().toDouble();
	//	smp86xHandler->start(2, (z/pulseEquivalent2 - ss.axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
	//}
}

void RunParams::on_pushButton_2_clicked()
{
	QAction* action = QMenu::exec(QList<QAction*>() << ui->actionGetPos << ui->actionGotoXY << ui->actionGotoZ, QCursor::pos());
	if (action == ui->actionGetPos)
	{
		QSettings settings;
		SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
		double pulseEquivalent0 = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
		double pulseEquivalent1 = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
		double pulseEquivalent2 = settings.value(QString("PulseEquivalent0/2"), 0.01).toDouble();
		ui->lineEdit_11->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent0, 0, 'f', 3));
		ui->lineEdit_12->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent1, 0, 'f', 3));
		ui->lineEdit_13->setText(QString("%1").arg(ss.axis_status[2].logicPos*pulseEquivalent2, 0, 'f', 3));
	}
	if (action == ui->actionGotoXY)
	{
		QSettings settings;
		SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
		double pulseEquivalent0 = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
		double pulseEquivalent1 = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
		double x = ui->lineEdit_11->text().toDouble();
		double y = ui->lineEdit_12->text().toDouble();
		smp86xHandler->start(0, 1, (x/pulseEquivalent0 - ss.axis_status[0].logicPos), (y/pulseEquivalent1 - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
	//if (action == ui->actionGotoZ)
	//{
	//	QSettings settings;
	//	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	//	double pulseEquivalent2 = settings.value(QString("PulseEquivalent0/2"), 0.01).toDouble();
	//	double z = ui->lineEdit_13->text().toDouble();
	//	smp86xHandler->start(2, (z/pulseEquivalent2 - ss.axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
	//}
}

void RunParams::on_toolButton_clicked()
{
	//QSettings settings;
	QString path = QFileDialog::getExistingDirectory(this, QString::fromUtf16(L"选择路径"), ui->lineEdit_5->text());
	if (!path.isEmpty())
	{
		//settings.setValue("BadMark/path", path);
		ui->lineEdit_5->setText(path);
		//ui->lineEdit_5->setText("\""+path+"\"");
	}
}

void RunParams::on_toolButton_2_clicked()
{
	//QSettings settings;
	QString path = QFileDialog::getExistingDirectory(this, QString::fromUtf16(L"选择路径"), ui->lineEdit_24->text());
	if (!path.isEmpty())
	{
		//settings.setValue("TimeRecord/path", path);
		ui->lineEdit_24->setText(path);
		//ui->lineEdit_5->setText("\""+path+"\"");
	}

}

void RunParams::on_lineEdit_14_textEdited(const QString &text)
{
	int total = ui->lineEdit_14->text().toInt();
	int from = ui->lineEdit_17->text().toInt();
	QByteArray first = nextCode();
	for(int i=0; i<from; i++)
		first = nextCode(first);
//	ui->lineEdit_15->setText(first);
	for(int i=from; i<from+total-1; i++)
		first = nextCode(first);
//	ui->lineEdit_16->setText(first);
}

void RunParams::on_lineEdit_17_textEdited(const QString &text)
{
	on_lineEdit_14_textEdited(text);
}

void RunParams::on_pushButton_3_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf16(L"导出"), "", QString::fromUtf16(L"文本文件(*.txt)"));
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if(file.open(QFile::WriteOnly|QFile::Text))
		{
			QTextStream out(&file);
			int total = ui->lineEdit_14->text().toInt();
			//QByteArray first = ui->lineEdit_15->text().toLatin1();
			//QByteArray prefix = ui->lineEdit_2->text().toLatin1();
			//QByteArray subfix = ui->lineEdit_4->text().toLatin1();
			out << total << "\r\n";
// 			for(int i=0; i<total; i++)
// 			{
// 				out << prefix+first+subfix << "\r\n";
// 				first = nextCode(first);
// 			}
			file.close();
			QProcess::startDetached("notepad.exe", QStringList() << fileName);
		}
		else
			QMessageBox::information(this, QString::fromUtf16(L"错误"), QString::fromUtf16(L"文件打开失败"));
	}
}

void RunParams::mouseDoubleClickEvent( QMouseEvent *event )
{
	//if (ui->lineEdit_15->rect().contains(ui->lineEdit_15->mapFromGlobal(event->globalPos())))
	//{
	//	ui->lineEdit_3->setText(ui->lineEdit_15->text());
	//}
	//return QWidget::mouseDoubleClickEvent(event);
}

