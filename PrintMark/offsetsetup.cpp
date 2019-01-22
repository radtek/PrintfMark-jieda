#include "stdafx.h"
#include "offsetsetup.h"
#include "ui_offsetsetup.h"

OffsetSetup::OffsetSetup(Smp86xHandler* sh, QTcpSocket* tcp1, QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint)
	, smp86xHandler(sh)
	, tcpSocket(tcp1)
{
	ui = new Ui::OffsetSetup();
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	QSettings settings;
	ui->lineEdit->setText(settings.value("Offset/pm0_x", "0.000").toString());
	ui->lineEdit_2->setText(settings.value("Offset/pm0_y", "0.000").toString());
	ui->lineEdit_3->setText(settings.value("Offset/cam0_x", "0.000").toString());
	ui->lineEdit_4->setText(settings.value("Offset/cam0_y", "0.000").toString());
	ui->label_4->setText(settings.value("Offset/center_x", "0.000").toString());
	ui->label_5->setText(settings.value("Offset/center_y", "0.000").toString());
	ui->lineEdit_5->setText(settings.value("Offset/pm1_x", "0.000").toString());
	ui->lineEdit_6->setText(settings.value("Offset/pm1_y", "0.000").toString());
	ui->lineEdit_7->setText(settings.value("Offset/pm1_u", "0.000").toString());
	ui->lineEdit_8->setText(settings.value("Offset/cam1_x", "0.000").toString());
	ui->lineEdit_9->setText(settings.value("Offset/cam1_y", "0.000").toString());
	ui->lineEdit_10->setText(settings.value("Offset/cam1_u", "0.000").toString());
	ui->label_6->setText(settings.value("Offset/ofs_x", "0.000").toString());
	ui->label_7->setText(settings.value("Offset/ofs_y", "0.000").toString());
	ui->label_8->setText(settings.value("Offset/ofs_u", "0.000").toString());
}

OffsetSetup::~OffsetSetup()
{
	delete ui;
}

void OffsetSetup::on_pushButton_clicked()
{
	QSettings settings;
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	double pulseEquivalent[4];
	pulseEquivalent[0] = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
	pulseEquivalent[1] = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
	ui->lineEdit  ->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
	ui->lineEdit_2->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
}

void OffsetSetup::on_pushButton_2_clicked()		//旋转中心
{
	QSettings settings;
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	double pulseEquivalent[4];
	pulseEquivalent[0] = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
	pulseEquivalent[1] = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
	ui->lineEdit_3->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
	ui->lineEdit_4->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));

	//double ix = 0.0, iy = 0.0, ia = 0.0;
	////sendTcpData(tcpSocket, 2);
	////bool ret = readTcpData(tcpSocket, &ix, &iy, &ia);

	//QTransform trans[4];
	////QList<QVariant> data1 = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());
	//trans[0] = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());

	////int resx[4], resy[4];
	////resx[0] = settings.value("Calibration/res_w1", 0).toInt();
	////resy[0] = settings.value("Calibration/res_h1", 0).toInt();

	////ix = ix - resx[0]/2.0;	iy = iy - resy[0]/2.0;
	//QPointF p; float u1;
	//affine_trans_xyu(trans[0], QPointF(iy, ix), ia*M_PI/180.0, p, u1);
	//u1 = u1*180.0/M_PI;
	//p = trans[0].map(QPointF()) - p + QPointF(ss.axis_status[0].logicPos*pulseEquivalent[0], ss.axis_status[1].logicPos*pulseEquivalent[1]);

	//ui->lineEdit_3->setText(QString("%1").arg(p.x(), 0, 'f', 3));
	//ui->lineEdit_4->setText(QString("%1").arg(p.y(), 0, 'f', 3));
}

void OffsetSetup::on_pushButton_3_clicked()
{
	double x1, y1, x2, y2;
	x1 = ui->lineEdit->text().toDouble();
	y1 = ui->lineEdit_2->text().toDouble();
	x2 = ui->lineEdit_3->text().toDouble();
	y2 = ui->lineEdit_4->text().toDouble();
	ui->label_4->setText(QString("%1").arg(x1-x2, 0, 'f', 3));
	ui->label_5->setText(QString("%1").arg(y1-y2, 0, 'f', 3));
}

void OffsetSetup::on_pushButton_4_clicked()
{
	QSettings settings;
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	double pulseEquivalent[4];
	pulseEquivalent[0] = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
	pulseEquivalent[1] = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
	pulseEquivalent[3] = settings.value(QString("PulseEquivalent0/3"), 0.01).toDouble();
	ui->lineEdit_5->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
	ui->lineEdit_6->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
	ui->lineEdit_7->setText(QString("%1").arg(ss.axis_status[3].logicPos*pulseEquivalent[3], 0, 'f', 3));
}

void OffsetSetup::on_pushButton_5_clicked()
{
	QSettings settings;
	SMP86X_STATUS ss = smp86xHandler->getSmp86xStatus();
	double pulseEquivalent[4];
	pulseEquivalent[0] = settings.value(QString("PulseEquivalent0/0"), 0.01).toDouble();
	pulseEquivalent[1] = settings.value(QString("PulseEquivalent0/1"), 0.01).toDouble();
	pulseEquivalent[3] = settings.value(QString("PulseEquivalent0/3"), 0.01).toDouble();
	ui->lineEdit_8->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
	ui->lineEdit_9->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
	ui->lineEdit_10->setText(QString("%1").arg(ss.axis_status[3].logicPos*pulseEquivalent[3], 0, 'f', 3));

	//double ix = 0.0, iy = 0.0, ia = 0.0;
	//sendTcpData(tcpSocket, 0);
	//bool ret = readTcpData(tcpSocket, &ix, &iy, &ia);

	//QTransform trans[4];
	////QList<QVariant> data1 = settings.value("Calibration/data1", QList<QVariant>() << 1 << 0 << 0 << 0 << 1 << 0).toList();
	//trans[0] = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());

	//int resx[4], resy[4];
	//resx[0] = settings.value("Calibration/res_w1", 0).toInt();
	//resy[0] = settings.value("Calibration/res_h1", 0).toInt();

	//ix = ix - resx[0]/2.0;	iy = iy - resy[0]/2.0;
	//QPointF p; float u1;
	//affine_trans_xyu(trans[0], QPointF(iy, ix), ia*M_PI/180.0, p, u1);
	//u1 = u1*180.0/M_PI;
	//p = trans[0].map(QPointF()) - p + QPointF(ss.axis_status[0].logicPos*pulseEquivalent[0], ss.axis_status[1].logicPos*pulseEquivalent[1]);

	//ui->lineEdit_8->setText(QString("%1").arg(p.x(), 0, 'f', 3));
	//ui->lineEdit_9->setText(QString("%1").arg(p.y(), 0, 'f', 3));
	//ui->lineEdit_10->setText(QString("%1").arg(p.y(), 0, 'f', 3));
}

void OffsetSetup::on_pushButton_6_clicked()		// 计算偏移
{
	double x1, y1, u1, x2, y2, u2;
	x1 = ui->lineEdit_5->text().toDouble();
	y1 = ui->lineEdit_6->text().toDouble();
	u1 = ui->lineEdit_7->text().toDouble();
	x2 = ui->lineEdit_8->text().toDouble();
	y2 = ui->lineEdit_9->text().toDouble();
	u2 = ui->lineEdit_10->text().toDouble();
	ui->label_6->setText(QString("%1").arg(x1-x2, 0, 'f', 3));
	ui->label_7->setText(QString("%1").arg(y1-y2, 0, 'f', 3));
	ui->label_8->setText(QString("%1").arg(u1-u2, 0, 'f', 3));
}

void OffsetSetup::on_buttonBox_clicked( QAbstractButton * button )
{
	if (QDialogButtonBox::ApplyRole == ui->buttonBox->buttonRole(button))
	{
		QSettings settings;
		settings.setValue("Offset/pm0_x", ui->lineEdit->text());
		settings.setValue("Offset/pm0_y", ui->lineEdit_2->text());
		settings.setValue("Offset/cam0_x", ui->lineEdit_3->text());
		settings.setValue("Offset/cam0_y", ui->lineEdit_4->text());
		settings.setValue("Offset/center_x", ui->label_4->text());
		settings.setValue("Offset/center_y", ui->label_5->text());
		settings.setValue("Offset/pm1_x", ui->lineEdit_5->text());
		settings.setValue("Offset/pm1_y", ui->lineEdit_6->text());
		settings.setValue("Offset/pm1_u", ui->lineEdit_7->text());
		settings.setValue("Offset/cam1_x", ui->lineEdit_8->text());
		settings.setValue("Offset/cam1_y", ui->lineEdit_9->text());
		settings.setValue("Offset/cam1_u", ui->lineEdit_10->text());
		settings.setValue("Offset/ofs_x", ui->label_6->text());
		settings.setValue("Offset/ofs_y", ui->label_7->text());
		settings.setValue("Offset/ofs_u", ui->label_8->text());
	}
	if (QDialogButtonBox::RejectRole == ui->buttonBox->buttonRole(button))
		close();
	if (QDialogButtonBox::AcceptRole == ui->buttonBox->buttonRole(button))
		close();
}
