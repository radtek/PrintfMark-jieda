#include "stdafx.h"
#include "timerecord.h"
#include "ui_timerecord.h"

TimeRecord::TimeRecord(QWidget *parent)
	: QWidget(parent, Qt::Tool|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::TimeRecord())
	, runTime(0, 0, 0)
{
	setAttribute(Qt::WA_NativeWindow);
	ui->setupUi(this);
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [this](){
		ui->timeEdit_4->setTime(QTime(0,0,0,1).addMSecs(runTime.elapsed()));
	});
	timer->start(1000);
	static std::function<void()> f = [parent]() {
		QSettings settings;
		int run_time = settings.value("Maintain/run").toInt() + 10;
		int duration = settings.value("Maintain/duration", 360).toInt();
		settings.setValue("Maintain/run", run_time);
		if (run_time/3600 > duration)
		{
			//QMessageBox::information(parent, QString::fromUtf16(L"提示"), QString::fromUtf16(L"已到保养时间，请保养机台"), QMessageBox::Ok);
			//int ws_mode = settings.value("SFC/mode", 1).toInt();
			//QString msg;
			//QString _endpoint = settings.value("Sfc/endpoint").toString();
			//QString _station = settings.value("SFC/linename").toString();
			//if (ws_mode == 0)
			//	sfcWin->SwSendData(_station + ";30;" + strEmployee + ";2;", msg);
			//else
			//	sfcWin->SaveTestData(_endpoint, _station + ";30;" + strEmployee + ";2;", msg);
			//if (msg.mid(0, 2) != "OK")
			//{
			//	QMessageBox::information(parent, QString::fromUtf16(L"SFC错误"), QString::fromUtf16(L"记录保养开始失败\n") + msg, QMessageBox::Ok);
			//}
		}
		QTimer::singleShot(10000, f);
	};
	QTimer::singleShot(10000, f);
	runTime.start();
}

TimeRecord::~TimeRecord()
{
	delete ui;
}

void TimeRecord::setTime(int index, int msec)
{
	QTime time = QTime(0, 0, 0, 1).addMSecs(msec);
	switch (index)
	{
	case 0:
		ui->timeEdit->setTime(time);
		break;
	case 1:
		ui->timeEdit_2->setTime(time);
		break;
	case 2:
		ui->timeEdit_3->setTime(time);
		break;
	}
}

bool TimeRecord::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message;
	if (msg->message == WM_NCHITTEST)
	{
		*result = HTCAPTION;
		return true;
	}

	return QWidget::nativeEvent(eventType, message, result);
}

