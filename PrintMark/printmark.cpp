#include "stdafx.h"
#include "printmark.h"
#include "camcalibration.h"
#include "iomonitor.h"
#include "platformcontroller.h"
#include "syssetup.h"
#include "runparams.h"
#include "offsetsetup.h"
#include "PassWordDialog.h"
#include "conveyor.h"
#include "excelfun.cpp"
#include "database.h"
#include "sfcwin.h"
#include "ink.h"
#include "timerecord.h"
#include "SfcLogin.h"
#include "arraydatasetup.h"
#include "Moveposition.h"
#include "pyBattery.h"

double pulseEquivalent[4];
int chushi = 1;
int textprintf = 0;

#define _visionPos [&](float& x, float& y, float& u, int m)->bool{\
	bool b = false;\
	for(int i=0; i<3 && !b; i++) \
		b = visionPos(x, y, u, m); \
	return b; \
}

#define _visionValid [&]()->bool{\
	bool b = false;\
	for(int i=0; i<3 && !b; i++) \
		b = visionValid(); \
	return b; \
}
int readExcelData(const char* xlsFileName, ImportData& data)
{
	return 0;
}
extern int speedValue[15] = {0,};

#ifdef _OLD_VERSION
QByteArray genPrintData(const QString& text)
{
	return QString("\x1bOE%1%2\x04").arg(text.size(), 4, 10, QChar('0')).arg(text).toLatin1();
}
#else
QByteArray genPrintData(const QString& text)
{
	QByteArray str = text.toLatin1();
	QByteArray ret("\x02");
	for (int i = 1; str.length() > 0; i++)
	{
		ret.append("\x10").append(char(0x30 + i)).append(str.left(10));
		str = str.mid(10);
	}
	ret.append("\x03");
	return ret;
}
#endif

PrintMark::PrintMark(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::PrintMarkClass)
	, closeDown(false)
{
	sigStat.alarm = sigStat.red = sigStat.green = 1;
	sigStat.yellow = 0;
	printInfo.index = 0;
	setAttribute(Qt::WA_NativeWindow);
	memset(&procFlag, 0, sizeof(PROCFLAG));
	ui->setupUi(this);
	ui->scrollArea->setWidget(ui->frame);
	ui->pushButton_3->hide();
	ui->checkBox_2->hide();
	ui->checkBox_3->hide();

	ui->tableWidget_2->hide();
	ui->tableWidget_2->setColumnWidth(0, 35);
	ui->tableWidget->setColumnWidth(0, 35);
	ui->tableWidget->setItemDelegate(new MyItemDelegate);
	connect(ui->tableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), 
		ui->tableWidget_2->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui->tableWidget_2->verticalScrollBar(), SIGNAL(valueChanged(int)), 
		ui->tableWidget->verticalScrollBar(), SLOT(setValue(int)));

// 	connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, [this](){
// 		drawToAngel();
// 	});

	ui->tableWidget_3->blockSignals(true);
	ui->tableWidget_3->setColumnWidth(0, 30);
	ui->tableWidget_3->item(0, 0)->setCheckState(Qt::Checked);
	ui->tableWidget_3->item(0, 3)->setFlags(ui->tableWidget_3->item(0, 3)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget_3->item(0, 4)->setFlags(ui->tableWidget_3->item(0, 4)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget_3->item(0, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget_3->item(0, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget_3->blockSignals(false);
#ifndef FoxlinkAdd
	ui->tableWidget_3->hide();
#endif // FoxlinkAdd

	ui->mainToolBar->addWidget(ui->pushButton_12);
	ui->mainToolBar->addWidget(ui->widget);
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addWidget(ui->widget_2);
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addWidget(ui->widget_3);
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addWidget(ui->pushButton_22);
	ui->mainToolBar->addSeparator();
// 	ui->mainToolBar->addWidget(ui->checkBox_6);
 	ui->mainToolBar->addWidget(ui->pushButton_23);
 	ui->mainToolBar->addWidget(ui->checkBox_8);
	ui->mainToolBar->addWidget(ui->checkBox_9);
	ui->mainToolBar->addWidget(ui->comboBox_2);
	ui->mainToolBar->addWidget(ui->pushButton_24);

	labelElapsed = new QLabel("Cycle Time: 0s");
	statusBar()->addPermanentWidget(labelElapsed);
	
	sfcWin = new SfcWin(this);
#ifdef FoxlinkAdd
	ui->lineEdit->setReadOnly(false);
	connect(ui->lineEdit, &QLineEdit::editingFinished, [this]() {
		setWindowModified(true);
	});
#else
	connect(sfcWin->ui->lineEdit, &QLineEdit::editingFinished, [this](){
		ui->lineEdit->setText(sfcWin->ui->lineEdit->text());
	});
#endif // FoxlinkAdd
// 	connect(sfcWin->ui->textEdit, &QTextEdit::textChanged, [this](){
// 		addMessage(sfcWin->ui->textEdit->toPlainText().trimmed(), Qt::blue);
// 	});

	timeRecord = new TimeRecord(this);
	
	QSettings settings;
	for(int i=0; i<15; i++)
		speedValue[i] = settings.value(QString("Speed/v%1").arg(i)).toInt();

	for (int i=0; i<4; i++)
		pulseEquivalent[i] = settings.value(QString("PulseEquivalent0/%2").arg(i), 0.01).toDouble();

	inteval = settings.value("Timer/inteval", 30).toInt();
	waitForUpChain = settings.value("TimeRecord/upchain", 0).toInt();
	waitForDownChain = settings.value("TimeRecord/downchain", 0).toInt();
	//QByteArray next = settings.value("Code/next", "0001").toString().toLatin1();
	//QByteArray prefix = settings.value("Code/prefix", "F0P54S").toString().toLatin1();
	//QByteArray subfix = settings.value("Code/subfix", "FY9Y9Z1").toString().toLatin1();
	//ui->lineEdit_2->setText(prefix+next+subfix);
	ui->checkBox_2->setChecked(settings.value("Print/flip", false).toBool());
	ui->checkBox_3->setChecked(settings.value("Print/reverse", false).toBool());
	ui->checkBox_5->setChecked(settings.value("first_station", false).toBool());

	ui->comboBox_2->setCurrentIndex(settings.value("Tcp/Changtext",0).toInt());
	curPrintf = settings.value("Tcp/Changtext", 0).toInt();

	ui->horizontalSlider->setValue(settings.value("ledbrightness").toInt());
	int timeout = settings.value("Smp86x/timeout", 500).toInt();
	for(int i=0; i<2; i++)
	{
#ifndef _OLD_VERSION
		if (i == 1)
		{
			smp86xHandler[1] = smp86xHandler[0];
			continue;
		}
#endif // _OLD_VERSION
		QString portName = settings.value(QString("Smp86x/port%1").arg(i+1), QString("COM%1").arg(i+1)).toString();
		//Smp86x* smp86x = /*(i == 0) ? new Smp86x("192.168.1.101", "502", timeout) : */new Smp86x(portName, 30);
		//smp86xHandler[i] = new Smp86xHandler(smp86x, 0xA);
		//QObject::connect(this, &PrintMark::endSmp86x, smp86xHandler[i], &QObject::deleteLater, Qt::DirectConnection);
		//QObject::connect(this, &PrintMark::endSmp86x, smp86x, &QObject::deleteLater, Qt::BlockingQueuedConnection);
		//QObject::connect(this, &PrintMark::endSmp86x, smp86x->thread(), &QThread::quit, Qt::QueuedConnection);
		//smp86x->thread()->start(QThread::TimeCriticalPriority);
		if (portName.isEmpty()) 
			portName = QString("COM%1").arg(i + 1);
		if (!QHostAddress(portName).isNull())
			smp86xHandler[i] = new Smp86xHandler(portName, "502", 0xA);
		else
			smp86xHandler[i] = new Smp86xHandler(portName, 0xA);
		QObject::connect(smp86xHandler[i], SIGNAL(homeQuestion()), this, SLOT(slotHomeQuestion()), Qt::QueuedConnection);
		Sleep(100);
		labelCom[i] = new QLabel(smp86xHandler[i]->isOpen() ? portName : "NULL");
		statusBar()->addPermanentWidget(labelCom[i]);
	}
	platform = new PlatformController(smp86xHandler, this);
	platform->layout()->setMargin(0);
	ui->horizontalLayout_5->addWidget(platform);
	connect(platform, SIGNAL(reset()), this, SLOT(slotHomeQuestion()));

	conveyor = new Conveyor(smp86xHandler[0],smp86xHandler[1], this);
	conveyor->hide();
// 	connect(conveyor->ui->pushButton, &QPushButton::clicked, ui->pushButton_19, &QPushButton::click);
// 	connect(conveyor->ui->pushButton_2, &QPushButton::clicked, ui->pushButton_20, &QPushButton::click);
// 	connect(conveyor->ui->pushButton_3, &QPushButton::clicked, ui->pushButton_21, &QPushButton::click);
	connect(ui->pushButton_19, &QPushButton::clicked, [this](){procFlag.conveyor_start = true;});
	connect(ui->pushButton_20, &QPushButton::clicked, [this](){
		procFlag.conveyor_start = true;
		procFlag.conveyor_ready = false;
	});
	connect(ui->pushButton_21, &QPushButton::clicked, [this](){
		procFlag.conveyor_start = false;
		procFlag.conveyor_ready = false;
#ifdef _OLD_VERSION
		smp86xHandler[1]->stopAll();
		smp86xHandler[1]->setOutput(0, 1);
		smp86xHandler[1]->setOutput(1, 1);
		smp86xHandler[1]->setOutput(8, 1);
		smp86xHandler[1]->setOutput(9, 1);
		smp86xHandler[1]->setOutput(10, 1);
#else
		smp86xHandler[0]->setOutput(0 + 16, 1);
		smp86xHandler[0]->setOutput(1 + 16, 1);
		smp86xHandler[0]->setOutput(5 + 16, 1);
		smp86xHandler[0]->setOutput(6 + 16, 1);
		smp86xHandler[0]->setOutput(7 + 16, 1);
		smp86xHandler[0]->setOutput(8 + 16, 1);
		smp86xHandler[0]->setOutput(9 + 16, 1);
#endif // _OLD_VERSION
	});
	//½â·ÅUÖá
// 	smp86xHandler[0]->setOutput(7, 0);

	tabWidget = new QTabWidget(this);
	tabWidget->setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
	tabWidget->setWindowTitle(QString::fromUtf16(L"IO¼àÊ¾Æ÷"));
	tabWidget->move(200, 100);
	//tabWidget->resize(500, 576);

	ioMonitor[0] = new IoMonitor(smp86xHandler[0], this);
	ioMonitor[0]->setLabels(QApplication::applicationDirPath() + "/iolabels1.ini");
	ioMonitor[0]->layout()->setMargin(0);
	tabWidget->addTab(new QWidget, "A");
	tabWidget->widget(0)->setLayout(new QHBoxLayout);
	tabWidget->widget(0)->layout()->addWidget(ioMonitor[0]);

#ifdef _OLD_VERSION
// 	ioMonitor[1] = new IoMonitor(smp86xHandler[1], this);
// 	ioMonitor[1]->setLabels(QApplication::applicationDirPath() + "/iolabels2.ini");
// 	ioMonitor[1]->layout()->setMargin(0);
// 	tabWidget->addTab(new QWidget, "B");
// 	tabWidget->widget(1)->setLayout(new QHBoxLayout);
// 	tabWidget->widget(1)->layout()->addWidget(ioMonitor[1]);
#else
	smp86xHandler[0]->start(3, -smp86xHandler[0]->getSmp86xStatus().axis_status[3].logicPos, 400000, 400000, 0.1);
#endif // _OLD_VERSION
	
//¸úÄ«Ë®»úµÄ´®¿ÚÁ¬½Ó
// 	QTcpSocket* ink_port = new QTcpSocket;
// 	QString ink_ip = settings.value("Print/ip", "192.168.1.10").toString();
// 	int po = settings.value("Print/ink_port", 16000).toInt();
// 	ink_port->connectToHost(QHostAddress(ink_ip), po);
// 	bool bConnected = ink_port->waitForConnected(5000);
// 	labelCom[3] = new QLabel(bConnected ? QString("%1:%2").arg(ink_ip).arg(po) : "NULL");
// 	ink_device = ink_port;

//////////////////////////////////////////////////////////////////////////
	int port_mode = settings.value("port_mode", 0).toInt();
	if(port_mode == 0)
	{
		QSerialPort* port = new QSerialPort();
		QString portName = settings.value("Print/port", "COM3").toString();
		port->setPortName(portName);
		port->setBaudRate(QSerialPort::Baud115200);
		port->setFlowControl(QSerialPort::NoFlowControl);
		port->setParity(QSerialPort::NoParity);
		port->setDataBits(QSerialPort::Data8);
		port->setStopBits(QSerialPort::OneStop);
		if(port->open(QIODevice::ReadWrite))
			labelCom[2] = new QLabel(portName);
		else
			labelCom[2] = new QLabel("NULL");
		device = port;
	}
	else
	{
		QTcpSocket* tcpSocket1 = new QTcpSocket;
		QString ip = settings.value("Tcp/ip", "192.168.1.10").toString();
		int p = settings.value("Tcp/port", 16000).toInt();
		tcpSocket1->connectToHost(QHostAddress(ip), p);
		bool bConnected = tcpSocket1->waitForConnected(5000);
		labelCom[2] = new QLabel(bConnected ? QString("%1:%2").arg(ip).arg(p) : "NULL");
		ink_device = tcpSocket1;
		connect(tcpSocket1, &QTcpSocket::disconnected, [this](){
			labelCom[2]->setText("NULL");
		});
		QTcpSocket* tcpSocket2 = new QTcpSocket;
		int p2 = settings.value("Tcp/port2", 7000).toInt();
		tcpSocket2->connectToHost(QHostAddress(ip), p2);
		bool bConnected2 = tcpSocket2->waitForConnected(5000);
		labelCom[3] = new QLabel(bConnected2 ? QString("%1:%2").arg(ip).arg(p2) : "NULL");
		device = tcpSocket2;
		connect(tcpSocket2, &QTcpSocket::disconnected, [this]() {
			labelCom[3]->setText("NULL");
		});
 	}
	//ÉèÖÃ²»·´À¡£¬Çå¿ÕÅçÂë»ú»º´æ¶ÓÁÐ
	QByteArray device_data = QString("I12OE00000").toLatin1();
	QByteArray device_data2 = QString("I1 ").toLatin1();
	if (labelCom[2]->text() != "NULL")
	{
		sendpre = sendPrintData(device, device_data);
		sendpre2 = sendPrintData(device, device_data2);
	}
	if (!sendpre && !sendpre2)
		QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨½øÐÐ³õÊ¼»¯\n"), QString::fromUtf16(L"È·¶¨"));
	statusBar()->addPermanentWidget(labelCom[2]);
	labelCom[2]->setStyleSheet("color:#660099;");
// 	statusBar()->addPermanentWidget(labelCom[3]);
// 	labelCom[3]->setStyleSheet("color:#660099;");

	connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_F10), this), SIGNAL(activated()), this, SLOT(slotMSettings()));
	connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A), this), &QShortcut::activated, [this](){
		static int c = 1;
		if((c++ % 10) == 0)
		{
			QIcon icon = this->windowIcon();
			this->setWindowIcon(QIcon(QStringLiteral(":/Resources/About.png")));
			QMessageBox::about(this, QString::fromUtf16(L"¹ØÓÚÈí¼þ"), QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³\n°æÈ¨ËùÓÐ\xa9 2015 Waltrontech LTD."));
			this->setWindowIcon(icon);
		}
	});
	// ´´½¨Ïà»ú´°¿Ú
	QString exeName = QString("IM2.exe");
	QProcess().execute(QString("taskkill.exe /f /im %1").arg(exeName));

	if (!QProcess::startDetached("IM2/IM2.exe", QStringList() << "1"))
		goto PASSC;
	WId wid = (WId)0;
	QTime t; t.restart();
	do	wid = (WId)FindWindow(L"Qt5QWindowIcon", L"IM2");
	while (!wid && t.elapsed() < 10000);
	if (!wid) goto PASSC;
	::Sleep(200);
	QWindow *m_window = QWindow::fromWinId(wid);
	QWidget* m_widget = QWidget::createWindowContainer(m_window, nullptr, Qt::Window);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_widget);
	ui->frame->setLayout(layout);
PASSC:
//  	PROCESS_INFORMATION pi[1];
//  	ZeroMemory(pi, sizeof(PROCESS_INFORMATION));
//  
//  	STARTUPINFOA si[1];
//  	ZeroMemory(si, sizeof(STARTUPINFO));
//  
//  	// Start the child process. 
//  	CreateProcessA("im2/IM2.exe",
//  		QString("%1").arg((int)ui->frame->winId()).toLatin1().data(),
//  		NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
//  		NULL, NULL, &si[0], &pi[0]);
//  
//  	WaitForInputIdle(pi[0].hProcess, 5000);

	labelTcp = new QLabel("NULL");
	statusBar()->addPermanentWidget(labelTcp);

	QTimer* timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, &QTimer::timeout, [this](){
		tcpSocket = new QTcpSocket;
		tcpSocket->connectToHost(QHostAddress(QHostAddress::LocalHost), 5800);
		bool bConnected = tcpSocket->waitForConnected(5000);
		labelTcp->setText(bConnected ? "Connected" : "Disconnected");
		QObject::connect(tcpSocket, &QTcpSocket::disconnected, [=](){
			labelTcp->setText("NULL");
		});
		QSettings settings;

// 		HWND hWnd = ::GetWindow((HWND)ui->frame->winId(), GW_CHILD);
// 		while (hWnd != NULL)
// 		{
// 
// 			TCHAR buf[128];
// 			::GetWindowTextW(hWnd, buf, 128);
// 			if (QString::fromUtf16(buf).startsWith("ImageMatching"))
// 			{
// 				EnableWindow(hWnd, FALSE);
// 				break;
// 			}
// 
// 			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
// 		}

#ifdef FoxlinkAdd
// 		SfcLogin login(this);
// 		if(QDialog::Accepted == login.exec())
// 		{
// 			QString _station = settings.value("SFC/linename").toString();
// 			QString emp_name = login.getName();//QInputDialog::getText(this, QString::fromUtf16(L"²Ù×÷Ô±µÇÂ¼"), QString::fromUtf16(L"Ãû³Æ"));
// 			if (!SaveTestData(_station + ";1;" + emp_name + ";"))
// 			{
// 				QMessageBox::information(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"²Ù×÷Ô±µÇÂ¼Ê§°Ü\n"), QString::fromUtf16(L"ÍË³ö"));
// 				close();
// 			}
// 			strEmployee = emp_name.isEmpty() ? QString() : emp_name;
// 			ui->checkBox_4->setEnabled(false);
// 			ui->checkBox_4->setChecked(true);
// 			ui->mainToolBar->addWidget(ui->checkBox_5);
// 		}
// 		else
// 		{
			ui->menuBar->removeAction(ui->menu_D->menuAction());
			ui->actionSfc->setChecked(false);
			ui->tableWidget_3->setVisible(false);
			ui->checkBox_5->setVisible(false);
			//ui->pushButton_6->setVisible(false);
			ui->pushButton_19->setVisible(false);
			ui->pushButton_20->setVisible(false);
			//ui->pushButton_13->setVisible(false);
			ui->pushButton_14->setVisible(false);
			ui->pushButton_17->setVisible(false);
			ui->checkBox_6->setVisible(false);
			ui->checkBox_7->setVisible(false);
			ui->pushButton_13->setVisible(false);
			ui->checkBox->setVisible(false);
			ui->comboBox->setVisible(false);
			ui->pushButton_26->setVisible(false);
//		}
		ui->menu_S->removeAction(ui->actionSfc);
	//	ui->menu_S->removeAction(ui->actiondpyBattery);
#else
		ui->menuBar->removeAction(ui->menu_D->menuAction());
#endif // FoxlinkAdd
		QString fileName = settings.value("last").toString();
		if (!fileName.isEmpty() && doLoadProject(fileName))
		{
			setWindowModified(false);
			setWindowFilePath(fileName);
			setWindowTitle(QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³ - %1[*]").arg(fileName));
		}
		updateStatistics();
		drawToAngel();
	});
	connect(timer, &QTimer::timeout, this, &PrintMark::slotProcMcu);
	timer->start(1000);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &PrintMark::slotTimeout);
	timer->start(50);
	if (smp86xHandler[0]->isOpen())
		slotHomeQuestion();
	//´´½¨µçÁ¿´®¿ÚÍ¨Ñ¶
	QString comport = settings.value("Electricity/com", "COM1").toString();
	smp86xHandler[2] = new Smp86xHandler(comport, 1);
	//´´½¨ÆøÑ¹´®¿ÚÍ¨Ñ¶
	QString comport2 = settings.value("AirPressure/com", "COM2").toString();
	smp86xHandler[3] = new Smp86xHandler(comport2, 2);
#ifdef _OLD_VERSION
	QTimer::singleShot(0, this, SLOT(slotCheckExpire()));
	QTimer::singleShot(0, this, SLOT(slotRenewCode()));
#endif // _OLD_VERSION
}

PrintMark::~PrintMark()
{
	delete ui;
}

void PrintMark::closeEvent( QCloseEvent *event )
{
	QSettings settings;
	if (isWindowModified())
	{
		int respond = QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"·½°¸±»ÐÞ¸Ä,ÊÇ·ñÒª±£´æ·½°¸?"), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
		switch (respond)
		{
		case QMessageBox::Cancel:
			event->setAccepted(false);
			return;
		case QMessageBox::Save:
			if(!windowFilePath().isEmpty())
				doSaveProject(windowFilePath());
			else
			{
				QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf16(L"±£´æ·½°¸"), ui->lineEdit->text(), "·½°¸ÎÄ¼þ(*.pmd)");
				if(fileName.isEmpty())
				{
					event->setAccepted(false);
					return;
				}
				if(!fileName.endsWith("pmd"))
					fileName.append(".pmd");
				doSaveProject(fileName);
				settings.setValue("last", fileName);
			}
			break;
		case  QMessageBox::Discard:
			break;
		}
	}
	setWindowModified(false);
	//foreach (QTimer* t, findChildren<QTimer*>())
	//{
	//	disconnect(t, 0, this, 0);
	//}

	settings.setValue("ledbrightness", ui->horizontalSlider->value());
	settings.setValue("Print/flip", ui->checkBox_2->isChecked());
	settings.setValue("Print/reverse", ui->checkBox_3->isChecked());
	settings.setValue("first_station", ui->checkBox_5->isChecked());
	settings.setValue("TimeRecord/upchain", waitForUpChain);
	settings.setValue("TimeRecord/downchain", waitForDownChain);
	settings.setValue("save_close", true);
	settings.setValue("Tcp/Changtext",ui->comboBox_2->currentIndex());

	smp86xHandler[0]->setPWM(1, 100);
	smp86xHandler[0]->stopAll();
	smp86xHandler[1]->stopAll();
	smp86xHandler[0]->quit();
	smp86xHandler[1]->quit();
	::Sleep(1000);

	delete device;
	closeDown = true;

	HWND hWnd = ::GetWindow((HWND)ui->frame->winId(), GW_CHILD);
	while (hWnd != NULL)
	{
		HWND hWnd1 = GetWindow(hWnd, GW_CHILD);
/*		hWnd = ::GetWindow(hWnd, GW_CHILD);*/
		while (hWnd1 != NULL) 
		{
			TCHAR buf[128];
			::GetWindowTextW(hWnd1, buf, 128);
			if (QString::fromUtf16(buf).startsWith("IM2"))
			{
				::SendMessage(hWnd1, WM_CLOSE, 0, 0);
				break;
			}
		}
		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
	return QMainWindow::closeEvent(event);
}

void PrintMark::slotMSettings()
{
	static bool actived = false;
	QString password;
	if(ui->pushButton_12->isChecked() && !actived && !(password = QInputDialog::getText(this, QString::fromUtf16(L"ÖÆÔìÉÌÃÜÂë"), 
		QString::fromUtf16(L"ÊäÈëÃÜÂë: "), QLineEdit::Password)).isEmpty())
	{
		QCryptographicHash crypto(QCryptographicHash::Md5);   //¼ÓÃÜMd5
		crypto.addData(QByteArray().append(password));
		//QMessageBox::information(this, "aaa", crypto.result().toHex());
		if(crypto.result() == "\xf3\x79\xea\xf3\xc8\x31\xb0\x4d\xe1\x53\x46\x9d\x1b\xec\x34\x5e")   //666666
		{
			actived = true;
		}
	}
	if(actived)
	{
		ui->menu_H->addActions(QList<QAction*>() << ui->actionSysSetup << ui->actionCamCalib << ui->actionOffsetSetup << ui->actionRunCpk);
		ui->menu_H->popup(ui->menuBar->mapToGlobal(ui->menuBar->actionGeometry(ui->menu_H->menuAction()).bottomLeft()));
		QTimer* timer = new QTimer(this);
		connect(timer, &QTimer::timeout, [this](){
			ui->menu_H->removeAction(ui->actionSysSetup);
			ui->menu_H->removeAction(ui->actionCamCalib);
			ui->menu_H->removeAction(ui->actionOffsetSetup);
			ui->menu_H->removeAction(ui->actionRunCpk);
			actived = false;
		});
		timer->setSingleShot(true);
		timer->start(600000);
	}
}

void PrintMark::on_actionQuit_triggered()
{
	close();
}

void PrintMark::on_actionAbout_triggered()
{
	QMessageBox::about(this, QString::fromUtf16(L"¹ØÓÚÈí¼þ"), QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³\n°æÈ¨ËùÓÐ\xa9 2015"));
}

void PrintMark::on_actionIoPane_triggered()
{
	tabWidget->showNormal();
	tabWidget->setWindowState((tabWidget->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_actionSysSetup_triggered()
{
	SysSetup dlg(this);
	Sleep(100);
	if(QDialog::Accepted == dlg.exec())
	{
		
// 		smp86xHandler[0]->quit();
// 		::Sleep(500);
// 		smp86xHandler[1]->quit();
// 		::Sleep(505);

		QSettings settings;
		for (int i=0; i<4; i++)
			pulseEquivalent[i] = settings.value(QString("PulseEquivalent0/%2").arg(i), 0.01).toDouble();
		inteval = settings.value("Timer/inteval", 30).toInt();

// 		for(int i=0; i<2; i++)
// 		{
// #ifndef _OLD_VERSION
// 			if (i == 1)
// 			{
// 				smp86xHandler[1] = smp86xHandler[0];
// 				continue;
// 			}
// #endif // _OLD_VERSION
// 			QString portName = settings.value(QString("Smp86x/port%1").arg(i + 1), QString("COM%1").arg(i + 1)).toString();
// 			//Smp86x* smp86x = new Smp86x(portName);
// 			//smp86xHandler[i] = new Smp86xHandler(smp86x, 0xA);
// 			//QObject::connect(this, &PrintMark::endSmp86x, smp86xHandler[i], &QObject::deleteLater, Qt::DirectConnection);
// 			//QObject::connect(this, &PrintMark::endSmp86x, smp86x, &QObject::deleteLater, Qt::BlockingQueuedConnection);
// 			//QObject::connect(this, &PrintMark::endSmp86x, smp86x->thread(), &QThread::quit, Qt::QueuedConnection);
// 			//smp86x->thread()->start();
// 			if (portName.isEmpty()) portName = QString("COM%1").arg(i + 1);
// 			if (!QHostAddress(portName).isNull())
// 				smp86xHandler[i] = new Smp86xHandler(portName, "502", 0xA);
// 			else
// 				smp86xHandler[i] = new Smp86xHandler(portName, 0xA);
// 			Sleep(200);
// 			labelCom[i]->setText(smp86xHandler[i]->isOpen() ? portName : "NULL");
// 		}
// 		QObject::connect(smp86xHandler[0], SIGNAL(homeQuestion()), this, SLOT(slotHomeQuestion()), Qt::QueuedConnection);
// 		platform->setHandler(smp86xHandler);
// 		conveyor->setHandler(smp86xHandler[1]);
// 		ioMonitor[0]->setHandler(smp86xHandler[0]);
// #ifdef _OLD_VERSION
// 		ioMonitor[1]->setHandler(smp86xHandler[1]);
// #endif // _OLD_VERSION
		RunParams* runParams = findChild<RunParams*>();
		if(runParams) runParams->setHandler(smp86xHandler[0]);
		int port_mode = settings.value("port_mode", 0).toInt();

		if (device->isOpen())
			delete device;

		if (port_mode != 0)
		{
			if (ink_device->isOpen())
				delete ink_device;
		}
		

		if(port_mode == 0)
		{
			QSerialPort* port = new QSerialPort();
			QString portName = settings.value("Print/port", "COM3").toString();
			port->setPortName(portName);
			port->setBaudRate(QSerialPort::Baud115200);
			port->setFlowControl(QSerialPort::NoFlowControl);
			port->setParity(QSerialPort::NoParity);
			port->setDataBits(QSerialPort::Data8);
			port->setStopBits(QSerialPort::OneStop);
			if(port->open(QIODevice::ReadWrite))
				labelCom[2]->setText(portName);
			else
				labelCom[2]->setText("NULL");
			device = port;
		}
		else
		{
			QTcpSocket* tcpSocket1 = new QTcpSocket;
			QString ip = settings.value("Tcp/ip", "192.168.1.10").toString();
			int p = settings.value("Tcp/port", 16000).toInt();
			tcpSocket1->connectToHost(QHostAddress(ip), p);
			bool bConnected = tcpSocket1->waitForConnected(5000);
			labelCom[2]->setText(bConnected ? QString("%1:%2").arg(ip).arg(p) : "NULL");
			ink_device = tcpSocket1;
			connect(tcpSocket1, &QTcpSocket::disconnected, [this](){
				labelCom[2]->setText("NULL");
			});
			QTcpSocket* tcpSocket2 = new QTcpSocket;
			int p2 = settings.value("Tcp/port2", 7000).toInt();
			tcpSocket2->connectToHost(QHostAddress(ip), p2);
			bool bConnected2 = tcpSocket2->waitForConnected(5000);
			labelCom[3] = new QLabel(bConnected2 ? QString("%1:%2").arg(ip).arg(p2) : "NULL");
			device = tcpSocket2;
			connect(tcpSocket2, &QTcpSocket::disconnected, [this]() {
				labelCom[3]->setText("NULL");
			});
		}
	}
}

void PrintMark::on_actionink_triggered()
{
	ink ink(this);
	if (QDialog::Accepted == ink.exec())
	{

	}
}

void PrintMark::on_actionCamCalib_triggered()
{
	CamCalibration* camcalib = findChild<CamCalibration*>();
	if (!camcalib)
	{
		camcalib = new CamCalibration(smp86xHandler[0], tcpSocket, this);
	}
	camcalib->showNormal();
	camcalib->raise();
	camcalib->setWindowState((camcalib->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_actionOffsetSetup_triggered()
{
	OffsetSetup* offsetSetup = findChild<OffsetSetup*>();
	if (!offsetSetup)
	{
		offsetSetup = new OffsetSetup(smp86xHandler[0], tcpSocket, this);
	}
	offsetSetup->setHandler(smp86xHandler[0]);
	offsetSetup->showNormal();
	offsetSetup->raise();
	offsetSetup->setWindowState((offsetSetup->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_actionNew_triggered()
{
	if (!isWindowModified() || QMessageBox::Discard == QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"·½°¸ÒÑ±»ÐÞ¸Ä,ÇëÏÈ±£´æ!"), QMessageBox::Discard|QMessageBox::Cancel))
	{
		ui->tableWidget->clearContents();
		ui->tableWidget->setRowCount(0);
		ui->tableWidget_2->clearContents();
		ui->tableWidget_2->setRowCount(0);
		markData[0].firstPos = markData[1].firstPos = QVector3D();
		ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
		ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
		ui->label_4->setToolTip(ui->label_4->text());
		ui->label_5->setToolTip(ui->label_5->text());
		ui->lineEdit->setText("");
		setWindowModified(false);
		setWindowFilePath(QString());
		setWindowTitle(QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³ - Î´±£´æ[*]"));
	}
}

void PrintMark::on_actionRunParams_triggered()
{
	RunParams* runParams = findChild<RunParams*>();
	if (!runParams)
	{
		runParams = new RunParams(smp86xHandler[0], this);
		connect(runParams, SIGNAL(paramsChanged()), this, SLOT(updateStatistics()));
	}
	runParams->show();
	runParams->raise();
	runParams->setWindowState((runParams->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_pushButton_clicked()// ÅçÂë
{
	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
	if (!ui->checkBox_9->isChecked())
	{
		bool exit1 = printfCurText();
		if (!exit1)
		{
			QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"Êý¾ÝÎÞ·¨·¢ËÍ£¬Çë¼ì²éÅçÂë»ú"));
			return;
		}
		updateStatistics();
	}
	QSettings settings;
	int dist = settings.value("Print/dist", 10000).toInt();
	double angle = settings.value("Print/angle", 0).toDouble();
	double printz = settings.value("Print/z", 0).toDouble();
	double printu = settings.value("Print/u", 0).toDouble();
	int dist1 = dist*cos(angle*M_PI/180);
	int dist2 = dist*sin(angle*M_PI/180);
// 	int delay = settings.value("Print/delay", 100).toInt();
	flyprintf.enabled = 1;
	flyprintf.order = 1;
	flyprintf.pin = 2;
	flyprintf.target = 2;
	double posOrder0 = ss.axis_status[0].logicPos;
	double posOrder1 = ss.axis_status[1].logicPos;

	smp86xHandler[0]->setOutput(0, ui->checkBox_2->isChecked() ? 0 : 1);
	smp86xHandler[0]->setOutput(1, ui->checkBox_3->isChecked() ? 0 : 1);
	if (angle == 0)
	{
		flyprintf.Pos[0] = posOrder0;
		smp86xHandler[0]->start(0,  -offsetFly, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
		flyprintf.axis = 0;
		flyprintf.mode = 1;
		
	}
	if (angle == 90)
	{
		flyprintf.Pos[0] = posOrder1;
		smp86xHandler[0]->start(1, - offsetFly, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
		flyprintf.axis = 1;
		flyprintf.mode = 1;
	}
	if (angle == 180)
	{
		flyprintf.Pos[0] = posOrder0;
		flyprintf.axis = 0;
		flyprintf.mode = 2;
		smp86xHandler[0]->start(0, offsetFly, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
	}
	if (angle == -90)
	{
		flyprintf.Pos[0] = posOrder1;
		flyprintf.axis = 1;
		flyprintf.mode = 2;
		smp86xHandler[0]->start(1, offsetFly, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
	}
	if (smp86xHandler[0]->writeRawData(0x180, sizeof(flyprintf)/2 , (ushort *)&flyprintf) == -1)
		QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"Êý¾Ý´«ÊäÊ§°Ü"));
	QtConcurrent::run([this]() {
		Sleep(500);
		while (isRunning(smp86xHandler[0]->getSmp86xStatus()))  Sleep(50);
		printfmove();
	});
// 	QtConcurrent::run([this]() {
// 		while (!isRunning(smp86xHandler[0]->getSmp86xStatus()))  Sleep(50);
// 		smp86xHandler[0]->setOutput(2, 0);
// 	});
// 	Sleep(delay);
// 	QtConcurrent::run([this](){
// 		Sleep(500);
// 		while(isRunning(smp86xHandler[0]->getSmp86xStatus())) Sleep(100);
// 		smp86xHandler[0]->setOutput(2, 1);
// 	});
// 	bool exit5 = receivrSUCFlag(device);
// 	if (!exit5)
// 	{
// 		bool exit5 = receivrSUCFlag(device);
// 		if (!exit5)
// 		{
// 			QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"´òÓ¡Î´Íê³É£¬Çë¼ì²éÅçÂë»ú"));
// 			return;
// 		}
// 	}
}

bool PrintMark::doSaveProject( const QString& fileName )
{
	QString dataPath = QFileInfo(fileName).path()+"/"+QFileInfo(fileName).baseName()+"/";
	if(!QDir().exists(dataPath))
		QDir().mkpath(dataPath);

	if(tcpSocket->state() == QAbstractSocket::ConnectedState)
		tcpSocket->write(QString("save %1").arg(dataPath+QFileInfo(fileName).completeBaseName()+".im2").toLocal8Bit());

	QFile file(fileName);
	if(file.open(QFile::WriteOnly))
	{
		QDataStream stream(&file);
		stream.setByteOrder(QDataStream::LittleEndian);
		stream << ui->lineEdit->text();
		stream << markData[0].firstPos << markData[1].firstPos;
		stream << ui->tableWidget->rowCount();
		for (int i=0; i<ui->tableWidget->rowCount(); i++)
		{
			stream << ui->tableWidget->item(i, 0)->checkState();
			stream << ui->tableWidget->item(i, 1)->text();
			stream << ui->tableWidget->item(i, 2)->text();
			stream << ui->tableWidget->item(i, 5)->text(); 
			stream << ui->tableWidget->item(i, 5)->checkState();
			stream << ui->tableWidget->item(i, 6)->text();
			stream << QString("placehole3") << QString("placehole4");
			stream << QString("placehole5") << QString("placehole6") << QString("placehole7") << QString("placehole8");
		}
		stream << ui->checkBox->isChecked();
		stream << 0;
// 		for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
// 		{
// 			stream << ui->tableWidget_2->item(i, 1)->text();
// 			stream << ui->tableWidget_2->item(i, 2)->text();
// 		}

		QSettings settings;
		stream << settings.value("Position/mark1_x", 0).toString();
		stream << settings.value("Position/mark1_y", 0).toString();
		stream << settings.value("Position/mark1_z", 0).toString();
		stream << settings.value("Position/mark2_x", 0).toString();
		stream << settings.value("Position/mark2_y", 0).toString();
		stream << settings.value("Position/mark2_z", 0).toString();
		stream << ui->checkBox_4->isChecked();
		stream << ui->actionSfc->isChecked();

		stream << ui->tableWidget_3->rowCount();
		for (int i=0; i<ui->tableWidget_3->rowCount(); i++)
		{
			stream << ui->tableWidget_3->item(i, 1)->text();
			stream << ui->tableWidget_3->item(i, 2)->text();
		}
		stream << ui->tableWidget_3->item(0, 0)->checkState();
		stream << ui->comboBox->currentIndex();
		stream << settings.value("PrintfMessage/message-1", "").toString();
		stream << settings.value("PrintfMessage/message-2", "").toString();
		stream << settings.value("PrintfMessage/message-3", "").toString();
		stream << settings.value("PrintfMessage/message-4", "").toString();
		stream << settings.value("PrintfMessage/message-5", "").toString();
		stream << settings.value("PrintfMessage/message-6", "").toString();
		stream << settings.value("PrintfMessage/message-7", "").toString();
		stream << settings.value("PrintfMessage/message-8", "").toString();

		stream << settings.value("ink_printf/text_number", 0).toString();
		for (int i =0;i<settings.value("ink_printf/text_number", 0).toInt();i++)
		{
			stream << settings.value(QString("ink_printf/text%1").arg(i), 0).toString();
		}
		stream<< settings.value("ink_printf/first", 0000).toString();
		stream<< settings.value("ink_printf/code", 040020024000101).toString();
		stream<< settings.value("ink_printf/countcode", "0123456789").toString();
		stream << settings.value("Conveyor/XsetWide", 0).toString();
		//stream << settings.value("Delay/mark", 100).toString();
		//stream << settings.value("Delay/badm", 100).toString();
		//stream << settings.value("Delay/code", 100).toString();

		//stream << settings.value("Light/mark", 30).toString();
		//stream << settings.value("Light/badm", 30).toString();
		//stream << settings.value("Light/code", 30).toString();

		//stream << settings.value("Code/prefix", "F0P54S").toString();
		//stream << settings.value("Code/next", "0001").toString();
		//stream << settings.value("Code/subfix", "FY9Y9Z1").toString();
		//stream << settings.value("Code/total", "0").toString();
		//stream << settings.value("Code/from", "1").toString();
		//stream << settings.value("Code/first", "0001").toString();
		//stream << settings.value("Code/last", "0001").toString();

		//stream << settings.value("Position/makeup_x", 0).toString();
		//stream << settings.value("Position/makeup_y", 0).toString();
		file.close();
		return true;
		addMessage(QString::fromUtf16(L"·½°¸ÒÑ±£´æ"), Qt::blue);
	}
	return false;
}

bool PrintMark::doLoadProject( const QString& fileName )
{
	RunParams* runParams = findChild<RunParams*>();
	if(runParams) runParams->close();

	QString dataPath = QFileInfo(fileName).path()+"/"+QFileInfo(fileName).baseName()+"/";
	if(tcpSocket->state() == QAbstractSocket::ConnectedState)
		tcpSocket->write(QString("load %1").arg(dataPath + QFileInfo(fileName).completeBaseName()+".im2").toLocal8Bit());
	markData[0].firstPos = markData[1].firstPos = QVector3D();
	QStringList strText1, strText2;
	strText1 << QString::fromUtf16(L"ÇëÑ¡Ôñ") << "P1" << "P2" << "P3" << "P4" << "P4" << "P4" << "P4";
	strText2 << QString::fromUtf16(L"ÇëÑ¡Ôñ") << "A" << "B" << "C" << "C" << "C" << "C";
	smp86xHandler[1]->setOutput(8, 1);
	smp86xHandler[1]->setOutput(9, 1);
	QFile file(fileName);
	if (file.open(QFile::ReadOnly))
	{
		QDataStream stream(&file);
		stream.setByteOrder(QDataStream::LittleEndian);

		int rowCount;QString text; 
		stream >> text;
		ui->lineEdit->setText(text);
		stream >> markData[0].firstPos >> markData[1].firstPos;
		markData[0].curntPos = markData[0].firstPos;
		markData[1].curntPos = markData[1].firstPos;
		ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
		ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
		ui->label_4->setToolTip(ui->label_4->text());
		ui->label_5->setToolTip(ui->label_5->text());

		stream >> rowCount;
		ui->tableWidget->setRowCount(rowCount);
		for (int i=0; i<rowCount; i++)
		{
			int checked, index;
			QBrush brush;
			stream >> checked;
			QTableWidgetItem* item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			item->setCheckState((Qt::CheckState)checked);
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget->setItem(i, 0, item);

			stream >> text;
			item = new QTableWidgetItem(text);
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(brush);
			ui->tableWidget->setItem(i, 1, item);

			stream >> text;
			item = new QTableWidgetItem(text);
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(brush);
			ui->tableWidget->setItem(i, 2, item);

			item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget->setItem(i, 3, item);

			item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget->setItem(i, 4, item);

			stream >> text;
			item = new QTableWidgetItem(QString("%1").arg(text.toInt()));
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(brush);
			ui->tableWidget->setItem(i, 5, item);

			stream >> checked;
			stream >> text;
			item = new QTableWidgetItem(text);
			item->setTextAlignment(Qt::AlignCenter);	
			item->setBackground(brush);
			ui->tableWidget->setItem(i, 6, item);
			item->setCheckState((Qt::CheckState)checked);

			for (int j=0; j<6; j++)
			{
				stream >> text;
			}
		}

		bool checked = false;
		stream >> checked;
		stream >> rowCount;
		ui->checkBox->setChecked(checked);
		ui->tableWidget_2->setVisible(checked);
		ui->tableWidget_2->setRowCount(rowCount);
		for (int i=0; i<rowCount; i++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignCenter);
			item->setCheckState(Qt::Unchecked);
			item->setFlags(item->flags()&(~Qt::ItemIsUserCheckable));
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget_2->setItem(i, 0, item);

			stream >> text;
			item = new QTableWidgetItem(text);
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget_2->setItem(i, 1, item);

			stream >> text;
			item = new QTableWidgetItem(text);
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget_2->setItem(i, 2, item);

			item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget_2->setItem(i, 3, item);

			item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			item->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
			item->setFlags(item->flags()&(~Qt::ItemIsEditable));
			ui->tableWidget_2->setItem(i, 4, item);
		}

		QSettings settings;
		stream >> text;
		//settings.setValue("Position/mark1_x", text);
		stream >> text;
		//settings.setValue("Position/mark1_y", text);
		stream >> text;
		//settings.setValue("Position/mark1_z", text);
		stream >> text;
		//settings.setValue("Position/mark2_x", text);
		stream >> text;
		//settings.setValue("Position/mark2_y", text);
		stream >> text;
		//settings.setValue("Position/mark2_z", text);
		stream >> checked;
		ui->checkBox_4->setChecked(checked);
		stream >> checked;
		checked = (checked /*&& ui->checkBox->isChecked()*/ && ui->checkBox_4->isChecked());
#ifdef FoxlinkAdd
		checked = !strEmployee.isNull();
#endif // FoxlinkAdd
		ui->actionSfc->setChecked(checked);
		//sfcWin->setVisible(checked);
		ui->tableWidget_3->setVisible(checked);
		//ui->checkBox->setEnabled(!checked&&ui->pushButton_12->isChecked());
		ui->checkBox_4->setEnabled(!checked&&ui->pushButton_12->isChecked());

		stream >> rowCount;
		//ui->tableWidget_3->setRowCount(rowCount);
		for (int i=0; i<rowCount; i++)
		{
			stream >> text;
			ui->tableWidget_3->item(0, 1)->setText(text);
			stream >> text;
			ui->tableWidget_3->item(0, 2)->setText(text);
		}
		stream >> rowCount;
		ui->tableWidget_3->item(0, 0)->setCheckState((Qt::CheckState)rowCount);
		stream >> rowCount;
		ui->comboBox->setCurrentIndex(rowCount);
		//stream >> text;
		//settings.setValue("Delay/mark", text);
		//stream >> text;
		//settings.setValue("Delay/badm", text);
		//stream >> text;
		//settings.setValue("Delay/code", text);

		//stream >> text;
		//settings.setValue("Light/mark", text);
		//stream >> text;
		//settings.setValue("Light/badm", text);
		//stream >> text;
		//settings.setValue("Light/code", text);

		//stream >> text;
		//settings.setValue("Code/prefix", text);
		//stream >> text;
		//settings.setValue("Code/next", text);
		//stream >> text;
		//settings.setValue("Code/subfix", text);
		//stream >> text;
		//settings.setValue("Code/total", text);
		//stream >> text;
		//settings.setValue("Code/from", text);
		//stream >> text;
		//settings.setValue("Code/first", text);
		//stream >> text;
		//settings.setValue("Code/last", text);

		//stream >> text;
		//settings.setValue("Position/makeup_x", text);
		//stream >> text;
		//settings.setValue("Position/makeup_y", text);
		file.close();

		QSettings settings1(QString(fileName).replace(QFileInfo(fileName).suffix(), "ini"), QSettings::IniFormat);
		settings.setValue("Position/mark1_x", settings1.value("Position/mark1_x", 0).toString());
		settings.setValue("Position/mark1_y", settings1.value("Position/mark1_y", 0).toString());
		settings.setValue("Position/mark1_z", settings1.value("Position/mark1_z", 0).toString());
		settings.setValue("Position/mark2_x", settings1.value("Position/mark2_x", 0).toString());
		settings.setValue("Position/mark2_y", settings1.value("Position/mark2_y", 0).toString());
		settings.setValue("Position/mark2_z", settings1.value("Position/mark2_z", 0).toString());

		settings.setValue("Delay/mark", settings1.value("Delay/mark", 100).toString());
		settings.setValue("Delay/badm", settings1.value("Delay/badm", 100).toString());
		settings.setValue("Delay/code", settings1.value("Delay/code", 100).toString());

		settings.setValue("Light/mark", settings1.value("Light/mark", 30).toString());
		settings.setValue("Light/badm", settings1.value("Light/badm", 30).toString());
		settings.setValue("Light/code", settings1.value("Light/code", 30).toString());

		settings.setValue("Code/prefix", settings1.value("Code/prefix", "F0P54S").toString());
		settings.setValue("Code/next", settings1.value("Code/next", "0001").toString());
		settings.setValue("Code/subfix", settings1.value("Code/subfix", "FY9Y9Z1").toString());
		settings.setValue("Code/total", settings1.value("Code/total", "0").toString());
		settings.setValue("Code/from", settings1.value("Code/from", "1").toString());
		settings.setValue("Code/first", settings1.value("Code/first", "0001").toString());
		settings.setValue("Code/last", settings1.value("Code/last", "0001").toString());

		settings.setValue("Position/makeup_x", settings1.value("Position/makeup_x", 0).toString());
		settings.setValue("Position/makeup_y", settings1.value("Position/makeup_y", 0).toString());
		//ui->lineEdit->setText(settings1.value("Sfc/order_no").toString());
		settings.setValue("PrintfMessage/message-1", settings1.value("PrintfMessage/message-1", 0).toString());
		settings.setValue("PrintfMessage/message-2", settings1.value("PrintfMessage/message-2", 0).toString());
		settings.setValue("PrintfMessage/message-3", settings1.value("PrintfMessage/message-3", 0).toString());
		settings.setValue("PrintfMessage/message-4", settings1.value("PrintfMessage/message-4", 0).toString());
		settings.setValue("PrintfMessage/message-5", settings1.value("PrintfMessage/message-5", 0).toString());
		settings.setValue("PrintfMessage/message-6", settings1.value("PrintfMessage/message-6", 0).toString());
		settings.setValue("PrintfMessage/message-7", settings1.value("PrintfMessage/message-7", 0).toString());
		settings.setValue("PrintfMessage/message-8", settings1.value("PrintfMessage/message-8", 0).toString());

		settings.setValue("ink_printf/text_number", settings1.value("ink_printf/text_number",0).toString());
		for (int i = 0; i < settings1.value("ink_printf/text_number", 0).toInt(); i++)
		{
			settings.setValue(QString("ink_printf/text%1").arg(i), settings1.value(QString("ink_printf/text%1").arg(i), 0).toString());
		}
		settings.setValue("ink_printf/first", settings1.value("ink_printf/first", 0000).toString());
		settings.setValue("ink_printf/code", settings1.value("ink_printf/code", 040020024000101).toString());
		settings.setValue("ink_printf/countcode", settings1.value("ink_printf/countcode", "0123456789").toString());
		settings.setValue("Conveyor/XsetWide", settings1.value("Conveyor/XsetWide", 0).toString());
		chushi = 1;
		return true;
	}
	return false;
}


void PrintMark::mouseDoubleClickEvent( QMouseEvent *event )
{
	if (ui->frame->rect().contains(ui->frame->mapFromGlobal(event->globalPos())))
	{
		QString exeName = QString("IM2.exe");
		QProcess().execute(QString("taskkill.exe /f /im %1").arg(exeName));

		if (!QProcess::startDetached("IM2/IM2.exe", QStringList() << "1"))
			goto PASSC1;
		WId wid = (WId)0;
		QTime t; t.restart();
		do	wid = (WId)FindWindow(L"Qt5QWindowIcon", L"IM2");
		while (!wid && t.elapsed() < 10000);
		if (!wid) goto PASSC1;
		::Sleep(200);
		QWindow *m_window = QWindow::fromWinId(wid);
		QWidget* m_widget = QWidget::createWindowContainer(m_window, nullptr, Qt::Window);
		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(m_widget);
		ui->frame->setLayout(layout);
	PASSC1:

// 		PROCESS_INFORMATION pi[1];
// 		ZeroMemory(pi, sizeof(PROCESS_INFORMATION));
// 
// 		STARTUPINFOA si[1];
// 		ZeroMemory(si, sizeof(STARTUPINFO));
// 		QByteArray b = QString::number(ui->frame->winId()).toLatin1();
// 		// Start the child process. 
// 		CreateProcessA("ImageMatching/ImageMatching.exe",	
// 			b.data(),
// 			NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE, 
// 			NULL, NULL, &si[0], &pi[0]);
// 
// 		WaitForInputIdle(pi[0].hProcess ,5000);
// 
		tcpSocket->connectToHost(QHostAddress(QHostAddress::LocalHost), 5800);    //5555
		bool bConnected = tcpSocket->waitForConnected(5000);
		labelTcp->setText(bConnected ? "Connected" : "Disconnected");
	}
	if (ui->label_4->rect().contains(ui->label_4->mapFromGlobal(event->globalPos())))
	{
		SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
		double x = markData[0].firstPos.x();
		double y = markData[0].firstPos.y();
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
		//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
	}
	if (ui->label_5->rect().contains(ui->label_5->mapFromGlobal(event->globalPos())))
	{
		SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
		double x = markData[1].firstPos.x();
		double y = markData[1].firstPos.y();
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
		//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
	}

	if (labelCom[2]->rect().contains(labelCom[2]->mapFromGlobal(event->globalPos())))
	{
		QSettings settings;
		int port_mode = settings.value("port_mode", 0).toInt();
		if(true)
		{
			delete ink_device,device;
			if(port_mode == 0)
			{
				QSerialPort* port = new QSerialPort();
				QString portName = settings.value("Print/port", "COM3").toString();
				port->setPortName(portName);
				port->setBaudRate(QSerialPort::Baud115200);
				port->setFlowControl(QSerialPort::NoFlowControl);
				port->setParity(QSerialPort::NoParity);
				port->setDataBits(QSerialPort::Data8);
				port->setStopBits(QSerialPort::OneStop);
				if(port->open(QIODevice::ReadWrite))
					labelCom[2]->setText(portName);
				else
					labelCom[2]->setText("NULL");
				device = port;
			}
			else
			{
				QTcpSocket* tcpSocket1 = new QTcpSocket;
				QString ip = settings.value("Tcp/ip", "192.168.1.10").toString();
				int p = settings.value("Tcp/port", 16000).toInt();
				tcpSocket1->connectToHost(QHostAddress(ip), p);
				bool bConnected = tcpSocket1->waitForConnected(5000);
				labelCom[2]->setText(bConnected ? QString("%1:%2").arg(ip).arg(p) : "NULL");
				ink_device = tcpSocket1;
				connect(tcpSocket1, &QTcpSocket::disconnected, [this](){
					labelCom[2]->setText("NULL");
				});
				QTcpSocket* tcpSocket2 = new QTcpSocket;
				int p2 = settings.value("Tcp/port2", 7000).toInt();
				tcpSocket2->connectToHost(QHostAddress(ip), p2);
				bool bConnected2 = tcpSocket2->waitForConnected(5000);
				labelCom[3] = new QLabel(bConnected2 ? QString("%1:%2").arg(ip).arg(p2) : "NULL");
				device = tcpSocket2;
				connect(tcpSocket2, &QTcpSocket::disconnected, [this]() {
					labelCom[3]->setText("NULL");
				});
			}
		}
	}
	QMainWindow::mouseDoubleClickEvent(event);
}

void PrintMark::on_pushButton_4_clicked()// ¿ªÊ¼
{
	if(procFlag.printing_start)
		return;
	if (ui->comboBox->currentIndex() == 1 && [this]()->bool{
		for (int i = 0; i < ui->tableWidget->rowCount(); i++)
			if (ui->tableWidget->item(i, 1)->text().toDouble() > 10 || ui->tableWidget->item(i, 2)->text().toDouble() > 10)
				return true;
		return false;
	}() && (0 == QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"),
		QString::fromUtf16(L"\"%1\"Ä£Ê½ÏÂÅçÂëXY×ø±êÎª²¹³¥Öµ,Çë¼ì²é!").arg(ui->comboBox->currentText()),
		QString::fromUtf16(L"¼ì²é"), QString::fromUtf16(L"¼ÌÐø¿ªÊ¼"))))
		return;
	if (ui->checkBox_5->isChecked() && ui->lineEdit->text().isEmpty())
	{
		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"×÷žéÍ¶ÈëÕ¾Ê±¹¤µ¥ºÅ²»ÄÜÎª¿Õ!"));
		return;
	}

	QSettings settings;
	double printz = settings.value("Print/z", 0).toDouble();
	double safez = settings.value("Smp86x/safe_z", 0).toDouble();

	SMP86X_STATUS ss[] = { smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus() };
	if (ui->tableWidget->rowCount() == 0)
		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"Êý¾ÝÎ´¼ÓÔØ"));
	//addMessage(QString::fromUtf16(L"Êý¾ÝÎ´¼ÓÔØ"), Qt::red);
	else if (tcpSocket->state() != QAbstractSocket::ConnectedState)
		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"ÊÓ¾õÄ£¿éÎ´¾ÍÐ÷"));
	//addMessage(QString::fromUtf16(L"ÊÓ¾õÄ£¿éÎ´¾ÍÐ÷"), Qt::red);
	else if (!device->isOpen() && !ui->checkBox_9->isChecked())
		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"ÅçÂë»úÎ´Á¬½Ó"));
	//addMessage(QString::fromUtf16(L"ÅçÂë»úÍ¨Ñ¶¹ÊÕÏ"), Qt::red);
// 	else if (!ink_device->isOpen())
// 		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"Ä«Ë®»úÍ¨Ñ¶¹ÊÕÏ"));
	else if(((ss[0].inputs>>4)&0x1) == 0)		// ÔÝÍ£
		QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"ÇëÏÈÈ¡ÏûÔÝÍ£°´¼ü"));
	//else if (printz < safez)
	//	addMessage(QString::fromUtf16(L"ÅçÂë¸ß¶ÈµÍÓÚ°²È«¸ß¶È"), Qt::red);
	else if(ui->listWidget_2->count() == 0 ||
		QMessageBox::Ok == QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"ÓÐ¹ÊÕÏÎ´Çå³ý,Çë¼ì²é¹ÊÕÏÁÐ±í\nÈ·¶¨Òª¿ªÊ¼?"), QMessageBox::Ok|QMessageBox::Cancel))
	{
		procFlag.conveyor_start = true;
		procFlag.conveyor_pass = false;
		procFlag.printing_start = true;
		procFlag.printing_pause = false;
		ui->pushButton_13->setChecked(false);
#ifdef _OLD_VERSION
// 		sendPrintData(device, QByteArray("\x1bOE00000\x04"));
// 		sendPrintData(device, QByteArray("\x1bOE00001\x04"));
// 		sendPrintData(device, QByteArray("\x1bOE00002\x04"));
#endif // _OLD_VERSION
		//smp86xHandler[0]->start(2, (printz/pulseEquivalent[2] - ss.axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		//QString text = ui->lineEdit_2->text();
		//QByteArray buff = QString("\x1bOE%1%2\x04").arg(text.size(), 4, 10, QChar('0')).arg(text).toLatin1();
		//device->write(buff);

		sigStat.alarm = sigStat.green = sigStat.yellow = sigStat.yellow = 1;
		runSignal(ss);
		
	}
}

void PrintMark::on_pushButton_5_clicked()// Í£Ö¹
{
	procFlag.conveyor_start = false;
	procFlag.conveyor_pass = false;
	procFlag.printing_start = false;
	procFlag.cpk_start = false;
	procFlag.scancode_start = false;
	ui->pushButton_13->setChecked(false);
	//smp86xHandler[0]->stopAll();
	//smp86xHandler[0]->stopAll();
	//smp86xHandler[0]->stopAll();
	procFlag.conveyor_ready = false;
	ushort flagstop[2] = { 0, };
	flagstop[0] = 1;
	smp86xHandler[0]->writeRawData(0x178, 1, (ushort*)flagstop);  //µ×²ãÅÐ¶Ï
#ifdef _OLD_VERSION
	smp86xHandler[0]->stopAll();
	smp86xHandler[1]->stopAll();
	smp86xHandler[0]->setOutput(0, 1);
	smp86xHandler[0]->setOutput(1, 1);
	smp86xHandler[0]->setOutput(2, 0);
	smp86xHandler[0]->setOutput(3, 1);
	smp86xHandler[0]->setOutput(4, 1);
	smp86xHandler[0]->setOutput(5, 1);
	smp86xHandler[0]->setOutput(6, 1);
	//smp86xHandler[1]->setOutput(10, 1);
#else
	smp86xHandler[0]->setOutput(0 + 16, 1);
	smp86xHandler[0]->setOutput(1 + 16, 1);
	smp86xHandler[0]->setOutput(5 + 16, 1);
	smp86xHandler[0]->setOutput(6 + 16, 1);
	smp86xHandler[0]->setOutput(7 + 16, 1);
	smp86xHandler[0]->setOutput(8 + 16, 1);
	smp86xHandler[0]->setOutput(9 + 16, 1);
#endif // _OLD_VERSION
}

void PrintMark::on_pushButton_6_clicked()
{
	conveyor->showNormal();
	conveyor->setWindowState((conveyor->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_pushButton_7_clicked()// Ìí¼Ó
{
	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();

	int row = ui->tableWidget->rowCount();
	ui->tableWidget->setRowCount(row+1);
	ui->tableWidget_2->setRowCount(row+1);

	QStringList itemText;
	itemText << "" << QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0]) << QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1]) << "" << "" << "0" << "" << "";

	for (int i=0; i<ui->tableWidget->columnCount(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignCenter);
		item->setText(itemText[i]);
		ui->tableWidget->setItem(row, i, item);

		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignCenter);
		item->setText(itemText[i]);
		ui->tableWidget_2->setItem(row, i, item);
	}

	ui->tableWidget->item(row, 0)->setCheckState(Qt::Checked);
	ui->tableWidget->item(row, 0)->setFlags(ui->tableWidget->item(row, 0)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget->item(row, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget->item(row, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget->item(row, 3)->setFlags(ui->tableWidget->item(row, 3)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget->item(row, 4)->setFlags(ui->tableWidget->item(row, 4)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget->item(row, 6)->setCheckState(Qt::Checked);
	ui->tableWidget->item(row, 6)->setText("001");
	ui->tableWidget->scrollToBottom();

	ui->tableWidget_2->item(row, 0)->setCheckState(Qt::Unchecked);
	ui->tableWidget_2->item(row, 0)->setFlags(ui->tableWidget_2->item(row, 0)->flags()&(~Qt::ItemIsUserCheckable));
	ui->tableWidget_2->item(row, 0)->setFlags(ui->tableWidget_2->item(row, 0)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget_2->item(row, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget_2->item(row, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
	ui->tableWidget_2->item(row, 3)->setFlags(ui->tableWidget_2->item(row, 3)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget_2->item(row, 4)->setFlags(ui->tableWidget_2->item(row, 4)->flags()&(~Qt::ItemIsEditable));
	ui->tableWidget_2->scrollToBottom();
	setWindowModified(true);
}

void PrintMark::on_pushButton_8_clicked()// É¾³ý
{
	int row = ui->tableWidget->currentRow();
	if (row != -1)
	{
		if (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), 
			QString::fromUtf16(L"¼´½«É¾³ýËùÑ¡ÐÐÊý¾Ý,²¢ÇÒ²»ÄÜ»Ö¸´,ÊÇ·ñ¼ÌÐøÖ´ÐÐ?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No))
		{
			QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
			QList<int> mylsit;
			int count = ranges.count();
			for (int i = 0; i < count; i++)
			{
				int topRow = ranges.at(i).topRow();
				int bottomRow = ranges.at(i).bottomRow();
				for (int j = bottomRow; j >= topRow; j--)
				{
					mylsit.push_back(j);
				}
			}
			qSort(mylsit.begin(),mylsit.end());
			for (int i = mylsit.size()-1; i >= 0;i--)
			{
				ui->tableWidget->removeRow(mylsit.at(i));
			}
			setWindowModified(true);
		}
	}
}

void PrintMark::on_pushButton_9_clicked()// ÉÏÒÆ
{
	int row = ui->tableWidget->currentRow();
	if (row > 0)
	{
		ui->tableWidget->blockSignals(true);
		for (int i=0; i<ui->tableWidget->columnCount(); i++)
		{
			QTableWidgetItem* item1 = ui->tableWidget->takeItem(row, i);
			QTableWidgetItem* item2 = ui->tableWidget->takeItem(row-1, i);
			ui->tableWidget->setItem(row, i, item2);
			ui->tableWidget->setItem(row-1, i, item1);
		}
		ui->tableWidget->blockSignals(false);
		ui->tableWidget->setCurrentCell(row-1, 0);

		ui->tableWidget_2->blockSignals(true);
		for (int i=0; i<ui->tableWidget_2->columnCount(); i++)
		{
			QTableWidgetItem* item1 = ui->tableWidget_2->takeItem(row, i);
			QTableWidgetItem* item2 = ui->tableWidget_2->takeItem(row-1, i);
			ui->tableWidget_2->setItem(row, i, item2);
			ui->tableWidget_2->setItem(row-1, i, item1);
		}
		ui->tableWidget_2->blockSignals(false);
		setWindowModified(true);
	}
}

void PrintMark::on_pushButton_10_clicked()// ÏÂÒÆ
{
	int row = ui->tableWidget->currentRow();
	if (row > -1 && row < ui->tableWidget->rowCount()-1)
	{
		ui->tableWidget->blockSignals(true);
		for (int i=0; i<ui->tableWidget->columnCount(); i++)
		{
			QTableWidgetItem* item1 = ui->tableWidget->takeItem(row, i);
			QTableWidgetItem* item2 = ui->tableWidget->takeItem(row+1, i);
			ui->tableWidget->setItem(row, i, item2);
			ui->tableWidget->setItem(row+1, i, item1);
		}
		ui->tableWidget->blockSignals(false);
		ui->tableWidget->setCurrentCell(row+1, 0);

		ui->tableWidget_2->blockSignals(true);
		for (int i=0; i<ui->tableWidget_2->columnCount(); i++)
		{
			QTableWidgetItem* item1 = ui->tableWidget_2->takeItem(row, i);
			QTableWidgetItem* item2 = ui->tableWidget_2->takeItem(row+1, i);
			ui->tableWidget_2->setItem(row, i, item2);
			ui->tableWidget_2->setItem(row+1, i, item1);
		}
		ui->tableWidget_2->blockSignals(false);
		setWindowModified(true);
	}
}

void PrintMark::on_pushButton_11_clicked()// ÆäËû
{
	QMenu menu;
	menu.addActions(QList<QAction*>() << ui->actionArraySetup << ui->actionMovePosition);
	menu.addSeparator();
	menu.addActions(QList<QAction*>() << ui->actionTrans << ui->actionSetMark1 << ui->actionSetMark2 << ui->actionClear);
	QAction* action = menu.exec(QCursor::pos());

	if (action == ui->actionArraySetup)
	{
		QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
		int count = ranges.count();
		if (count == 0)
		{
			QMessageBox::information(this, QString::fromUtf16(L"ÐÅÏ¢"), QString::fromUtf16(L"ÇëÑ¡ÔñÕóÁÐµÄÄ¿±ê!"));
			return;
		}
		ArrayDataSetup* setup = new ArrayDataSetup(ui->tableWidget);
		setup->setTable(ui->tableWidget, ui->tableWidget_2);
		setup->setHandler(smp86xHandler[0]);
		setup->show();
		ui->pushButton_7->setEnabled(false);
		ui->pushButton_8->setEnabled(false);
		connect(setup, &QWidget::destroyed, [this]() {
			ui->pushButton_7->setEnabled(ui->pushButton_12->isChecked());
			ui->pushButton_8->setEnabled(ui->pushButton_12->isChecked());
		});
		setup->setWindowState((setup->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	}

	if (action == ui->actionMovePosition)
	{
		Moveposition* move = new Moveposition(ui->tableWidget);
		move->setTable(ui->tableWidget);
		move->show();
		move->setWindowState((move->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	}

	if ((action == ui->actionClear) && (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), 
		QString::fromUtf16(L"´Ë²Ù×÷½«Çå¿ÕÁÐ±íËùÓÐÊý¾Ý,²¢ÇÒ²»ÄÜ»Ö¸´,ÊÇ·ñ¼ÌÐøÖ´ÐÐ?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No)))
	{
		ui->tableWidget->clearContents();
		ui->tableWidget->setRowCount(0);
		ui->tableWidget_2->clearContents();
		ui->tableWidget_2->setRowCount(0);
		markData[0].firstPos = markData[1].firstPos = QVector3D();
		ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
		ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
		ui->label_4->setToolTip(ui->label_4->text());
		ui->label_5->setToolTip(ui->label_5->text());
		setWindowModified(true);
		return;
	}
	if ((action == ui->actionSetMark1))
	{
		int index = ui->tableWidget->currentRow();
		if(index != -1 && (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"È·¶¨ÒªÉèÖÃ»ù×¼1?"), 
			QMessageBox::Yes|QMessageBox::No, QMessageBox::No)))
		{
			markData[0].firstPos.setX(ui->tableWidget->item(index, 2)->text().toDouble());
			markData[0].firstPos.setY(ui->tableWidget->item(index, 3)->text().toDouble());
			markData[0].firstPos.setZ(1.0);
			ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
			ui->label_4->setToolTip(ui->label_4->text());
			setWindowModified(true);
		}
	}
	if (action == ui->actionSetMark2)
	{
		int index = ui->tableWidget->currentRow();
		if(index != -1 && (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"È·¶¨ÒªÉèÖÃ»ù×¼2?"), 
			QMessageBox::Yes|QMessageBox::No, QMessageBox::No)))
		{
			markData[1].firstPos.setX(ui->tableWidget->item(index, 2)->text().toDouble());
			markData[1].firstPos.setY(ui->tableWidget->item(index, 3)->text().toDouble());
			markData[1].firstPos.setZ(1.0);
			ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
			ui->label_5->setToolTip(ui->label_5->text());
			setWindowModified(true);
		}
	}
	if (action == ui->actionTrans)
	{
		QTransform trans;
		if(vector_to_rigid(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF(), 
			markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF(), trans))
		{
			double x, y;
			QSettings settings;
			double makeup_x = settings.value("Position/makeup_x", 0).toDouble();
			double makeup_y = settings.value("Position/makeup_y", 0).toDouble();
			for (int i=0; i<ui->tableWidget->rowCount(); i++)
			{
				ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
				x = ui->tableWidget->item(i, 1)->text().toDouble()+makeup_x;
				y = ui->tableWidget->item(i, 2)->text().toDouble()+makeup_y;
				QPointF pos = trans.map(QPointF(x, y));
				ui->tableWidget->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
				ui->tableWidget->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
			}

			for (int i=0; i<ui->tableWidget_2->rowCount(); i++)
			{
				ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(i, 0));
				x = ui->tableWidget_2->item(i, 1)->text().toDouble();
				y = ui->tableWidget_2->item(i, 2)->text().toDouble();
				QPointF pos = trans.map(QPointF(x, y));
				ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
				ui->tableWidget_2->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
			}

			for (int i=0; i<ui->tableWidget_3->rowCount(); i++)
			{
				x = ui->tableWidget_3->item(i, 1)->text().toDouble();
				y = ui->tableWidget_3->item(i, 2)->text().toDouble();
				QPointF pos = trans.map(QPointF(x, y));
				ui->tableWidget_3->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
				ui->tableWidget_3->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
			}
		}
	}
}

void PrintMark::on_pushButton_12_clicked(bool checked)// ¹ÜÀíÔ±
{
	QSettings settings;
	PassWordDialog dlg(this);
	dlg.setPassWordString(settings.value("password", "\xd4\x1d\x8c\xd9\x8f").toString());
	if (checked && QDialog::Accepted != dlg.exec())
	{
		ui->pushButton_12->setChecked(false);
		return;
	} 

	RunParams* runParams = findChild<RunParams*>();
	if(runParams) runParams->close();
	sfcWin->hide();

	//ui->lineEdit->setReadOnly(!checked);
	ui->lineEdit_2->setReadOnly(!checked);
	//ui->lineEdit_3->setReadOnly(!checked);
	ui->checkBox->setEnabled(checked/*&&!ui->actionSfc->isChecked()*/);
	ui->comboBox->setEnabled(checked && ui->checkBox->isChecked());
	ui->checkBox_4->setEnabled(checked&&!ui->actionSfc->isChecked());
	ui->checkBox_5->setEnabled(checked);
	ui->pushButton_7->setEnabled(checked);
	ui->pushButton_8->setEnabled(checked);
	ui->pushButton_9->setEnabled(checked);
	ui->pushButton_10->setEnabled(checked);
	ui->actionSetMark1->setEnabled(checked);
	ui->actionSetMark2->setEnabled(checked);
	ui->actionClear->setEnabled(checked);
	ui->actionSysSetup->setEnabled(checked);
	ui->actionRunParams->setEnabled(checked);
	ui->actionSetup->setEnabled(checked);
	ui->actionReset->setEnabled(checked);
	ui->actionGetPos->setEnabled(checked);
	ui->actionCamCalib->setEnabled(checked);
	ui->actionOffsetSetup->setEnabled(checked);
	ui->actionSfcWin->setEnabled(checked);
	ui->actionMaintain1->setEnabled(checked);
	ui->actionMaintain2->setEnabled(checked);
	ui->tableWidget->setEditTriggers(checked ? QTableWidget::EditTrigger(10) : QTableWidget::NoEditTriggers);
	ui->tableWidget_2->setEditTriggers(checked ? QTableWidget::EditTrigger(10) : QTableWidget::NoEditTriggers);
	ui->tableWidget_3->setEditTriggers(checked ? QTableWidget::EditTrigger(10) : QTableWidget::NoEditTriggers);

	HWND hWnd = ::GetWindow((HWND)ui->frame->winId(), GW_CHILD);
	while (hWnd != NULL)
	{

		TCHAR buf[128];
		::GetWindowTextW(hWnd, buf, 128);
		if (QString::fromUtf16(buf).startsWith("ImageMatching"))
		{
			EnableWindow(hWnd, checked);
			break;
		}

		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
}

void PrintMark::on_pushButton_13_clicked(bool checked)
{
	procFlag.conveyor_pass = checked;
	if(checked)
	{
#ifdef _OLD_VERSION
		smp86xHandler[1]->setOutput(8, 1);
		smp86xHandler[1]->setOutput(9, 1);
	//	smp86xHandler[1]->setOutput(10, 1);
#else
		smp86xHandler[0]->setOutput(6+16, 1);
		smp86xHandler[0]->setOutput(7+16, 1);
#endif // _OLD_VERSION
		addMessage(QString::fromUtf16(L">>>Ö±Í¨Ä£Ê½>>>"), Qt::blue);
	}
}

void PrintMark::on_pushButton_15_clicked()		// Çå³ý±¨¾¯
{
	SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
	procFlag.code_empty_err = false;
	procFlag.printing_pause = (((ss.inputs>>6)&0x1) == 0);
#ifdef _OLD_VERSION
	smp86xHandler[1]->setOutput(3, 1);
#else
	smp86xHandler[0]->setOutput(18, 1);
#endif // _OLD_VERSION
	sigStat.alarm = 1;
}

void PrintMark::on_pushButton_16_clicked()
{
	static bool checked = false;
	checked = !checked;
	for (int i=0; i<ui->tableWidget->rowCount(); i++)
	{
		ui->tableWidget->item(i, 0)->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
	}
}

void PrintMark::on_checkBox_clicked( bool checked )
{
	ui->comboBox->setEnabled(checked);
	setWindowModified(true);
}

void PrintMark::on_comboBox_currentIndexChanged(int index)
{
	setWindowModified(true);
	//const char* text[] = { "\345\235\217\347\202\271", "\347\231\275\346\262\271" };
	//ui->tableWidget_2->horizontalHeaderItem(0)->setText(ui->comboBox->currentText());
}

void PrintMark::on_checkBox_4_clicked(bool checked)
{
	setWindowModified(true);
}

void PrintMark::on_actionSave_triggered()
{
	if(windowFilePath().isEmpty())
		on_actionSaveAs_triggered();
	else
	{
		QString fileName = windowFilePath();
		if(doSaveProject(fileName))
		{
			setWindowModified(false);

			QSettings settings;
			QSettings settings1(QString(fileName).replace(QFileInfo(fileName).suffix(), "ini"), QSettings::IniFormat);
			foreach(const QString&k, settings.allKeys())
			{
				settings1.setValue(k, settings.value(k).toString());
			}
		}
	}
}

void PrintMark::on_actionSaveAs_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf16(L"±£´æ·½°¸"), ui->lineEdit->text(), QString::fromUtf16(L"·½°¸ÎÄ¼þ(*.pmd)"));
	if(fileName.isEmpty())
		return;
	if(!fileName.endsWith("pmd"))
		fileName.append(".pmd");

	if (doSaveProject(fileName))
	{
		QSettings settings;
		settings.setValue("last", fileName);
		setWindowModified(false);
		setWindowFilePath(fileName);
		setWindowTitle(QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³ - %1[*]").arg(fileName));

		QSettings settings1(QString(fileName).replace(QFileInfo(fileName).suffix(), "ini"), QSettings::IniFormat);
		foreach(const QString&k, settings.allKeys())
		{
			settings1.setValue(k, settings.value(k).toString());
		}
	}
}

void PrintMark::on_actionLoad_triggered()
{
	if (isWindowModified())
	{
		int respond = QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"·½°¸±»ÐÞ¸Ä,ÊÇ·ñÒª±£´æ·½°¸?"), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
		switch (respond)
		{
		case QMessageBox::Cancel:
			return;
		case QMessageBox::Save:
			on_actionSave_triggered();
			break;
		case  QMessageBox::Discard:
			break;
		}
	}

	QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf16(L"ÔØÈë·½°¸"), "", QString::fromUtf16(L"·½°¸ÎÄ¼þ(*.pmd)"));
	if(!fileName.isEmpty() && doLoadProject(fileName))
	{
		QSettings settings;
		settings.setValue("last", fileName);
		setWindowModified(false);
		setWindowFilePath(fileName);
		setWindowTitle(QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³ - %1[*]").arg(fileName));
		updateStatistics();
	}
}



void PrintMark::slotHomeQuestion()
{
	static QMutex mutex;
	if(!mutex.tryLock())
		return;

	if(0 == QMessageBox::question(this, QString::fromUtf16(L"ÌáÐÑ"), 
		QString::fromUtf16(L"ÊÇ·ñ»ØÔ­µã£¿"), QString::fromUtf16(L"»ØÔ­µã"), QString::fromUtf16(L"È¡Ïû")))
	{
		procFlag.homing = true;
		ui->pushButton_4->setEnabled(true);
		ui->tableWidget->setEnabled(true);
		ui->tableWidget_2->setEnabled(true);
		ui->tableWidget_3->setEnabled(true);
	}
	else
	{
		ui->pushButton_4->setEnabled(false);
		ui->tableWidget->setEnabled(false);
		ui->tableWidget_2->setEnabled(false);
		ui->tableWidget_3->setEnabled(false);
	}

	mutex.unlock();
}

void PrintMark::slotProcMcu()
{
	if (closeDown)
		return;

	QTimer::singleShot(inteval, this, SLOT(slotProcMcu()));
	if (procFlag.real_time)::Sleep(30);
		
	SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(procFlag.real_time), smp86xHandler[1]->getSmp86xStatus()};
	procFlag.real_time = false;
 
	if (((ss[0].inputs >> 2) & 0x1) == 0)   //Ö±Í¨°´Å¥
	{
		procFlag.conveyor_pass = true;
	}
	if (((ss[0].inputs >> 2) & 0x1) == 1 && conveyorPass == 0)
	{
		on_pushButton_13_clicked(false);
		conveyorPass = 1;
	}
  	if (((ss[0].inputs >> 3) & 0x1) == 0 && startPu == 1)   //¿ªÊ¼°´ÏÂ
  	{
		startPu = 0;
 		if (labelCom[0]->text() != "NULL")
 		{
 			on_pushButton_4_clicked();
 		}	
  	}
	if (((ss[0].inputs >> 4) & 0x1) == 0 && pausePu == 1)   //ÔÝÍ£°´Å¥
	{
		pausePu = 0;
		on_pushButton_18_clicked();
	}
	if (((ss[0].inputs >> 4) & 0x1) == 1 && pausePu == 0)
	{
		procFlag.printing_pause = false;
		pausePu = 1;
	}
 	if (((ss[0].inputs >> 5) & 0x1) == 0 && clearPu == 1)     //Çå³ý±¨¾¯
	{
		clearPu = 0;
	    on_pushButton_15_clicked();
 	}
	conveyorPass = ((ss[0].inputs >> 2) & 0x1);
	startPu = ((ss[0].inputs >> 3) & 0x1);
	pausePu = ((ss[0].inputs >> 4) & 0x1);
	clearPu = ((ss[0].inputs >> 5) & 0x1);


	if (((ss[0].inputs>>9) & 0x1) == 1 )	// ¼±Í£°´ÏÂ
	{
		memset(&procFlag, 0, sizeof(PROCFLAG));
	}
 	else if (((ss[0].axis_status[0].state >> 15) & 0x1) == 1
 		|| ((ss[0].axis_status[1].state >> 15) & 0x1) == 1
		|| ((ss[0].axis_status[2].state >> 15) & 0x1) == 1
		)	// ËÅ·þ±¨¾¯
 	{
 		memset(&procFlag, 0, sizeof(PROCFLAG));
 	}
	else
	{
		runConveyor(ss);
		runPrinting(ss);
		runScanCode(ss);
		runCpk(ss);
		runHoming(ss);
	}
}

#if 0
void PrintMark::runConveyor(SMP86X_STATUS ss[])
{
	static int _step1 = 0, _step2 = 0;
	static QTime time;
	if(!procFlag.conveyor_start)
	{
		_step1 = 0;
		_step2 = 0;
		return;
	}

	switch(_step1)
	{
	case 0:
		if(((ss[1].inputs>>5) & 0x1) == 0 && _step2 < 80)	//ÒÑ¾­ÓÐ°åÔÚÖÐ¶Î
		{
			QSettings settings;
			int v1 = settings.value("Conveyor/speed_0", 1000).toInt();
			int v2 = settings.value("Conveyor/speed_1", 5000).toInt();
			int v3 = settings.value("Conveyor/speed_2", 500).toInt();
			smp86xHandler[1]->start(0, v1, -v2, v3/1000.0);	// Æô¶¯µç»ú1
			smp86xHandler[1]->setOutput(9, procFlag.conveyor_pass ? 1 : 0);	// ×èµ²ÉÏ
			if(procFlag.printing_start)
			{
				elapsedTimer.restart();
				elapsed = 0;
			}
			_step1 = 30;
			break;
		}

		if(((ss[1].inputs>>6) & 0x1) == 0)	//ÒÑ¾­ÓÐ°åÔÚµ½Î»
		{
			_step2 = 80;
		}

		smp86xHandler[1]->setOutput(1, 0);	// ¸øÉÏÎ»»úÐÅºÅ
		_step1 = 10;
		break;
	case 10:
		if (((ss[1].inputs>>3) & 0x1) == 0 || ((ss[1].inputs>>4) & 0x1) == 0)	// ÉÏÎ»»úÓÐÐÅºÅ,ÓÐ°å½øÀ´
		{
			QSettings settings;
			int v1 = settings.value("Conveyor/speed_0", 1000).toInt();
			int v2 = settings.value("Conveyor/speed_1", 5000).toInt();
			int v3 = settings.value("Conveyor/speed_2", 500).toInt();
			smp86xHandler[1]->start(0, v1, -v2, v3/1000.0);	// Æô¶¯µç»ú1
			if(procFlag.printing_start)
			{
				elapsedTimer.restart();
				elapsed = 0;
			}
			_step1 = 20;
		}
		break;
	case 20:
		if(((ss[1].inputs>>7) & 0x1) == 0)			//³öÁÏ¸ÐÓ¦
			break;

		if (((ss[1].inputs>>4) & 0x1) == 0 || ((ss[1].inputs>>5) & 0x1) == 0)	// ÓÐ°å½øÀ´
		{
			smp86xHandler[1]->setOutput(9, procFlag.conveyor_pass ? 1 : 0);	// ×èµ²ÉÏ
			_step1 = 30;
		}
		break;
	case 30:
		if (((ss[1].inputs>>13) & 0x1) == 0 || procFlag.conveyor_pass)	// ×èµ²µ½Î»
		{
			QSettings settings;
			int v1 = settings.value("Conveyor/speed_3", 1000).toInt();
			int v2 = settings.value("Conveyor/speed_4", 5000).toInt();
			int v3 = settings.value("Conveyor/speed_5", 500).toInt();
			smp86xHandler[1]->start(1, v1, -v2, v3/1000.0);	// Æô¶¯µç»ú2
			_step1 = 40;
		}
		break;
	case 40:
		if (((ss[1].inputs>>5) & 0x1) == 0)	// °å½øµ½µÚ¶þ¶Î
		{
			smp86xHandler[1]->setOutput(1, 1);	// ¹ØÉÏÎ»»úÐÅºÅ
			_step1 = 50;
		}
		break;
	case 50:
		if (((ss[1].inputs>>6) & 0x1) == 0)	//µÚ¶þ¶Îµ½Î»
		{
			smp86xHandler[1]->stop(0);
			time.restart();
			_step1 = 60;
		}
		break;
	case 60:
		if(time.elapsed() < 500)
			break;

		if(!procFlag.conveyor_pass)
		{
			smp86xHandler[1]->stop(1);
			//smp86xHandler[1]->setOutput(8, 0);	//²àÑ¹
		}
		_step1 = 72;
		break;
	case 70:
		if (((ss[1].inputs>>11) & 0x1) == 0 || procFlag.conveyor_pass)	//²àÑ¹µ½Î»
		{
			time.restart();
			_step1 = 71;
		}
		break;
	case 71:
		if(time.elapsed() < 100)
			break;

		smp86xHandler[1]->setOutput(8, 1);	//²àÑ¹
		_step1 = 72;
		break;
	case 72:
		if (((ss[1].inputs>>10) & 0x1) == 0 || procFlag.conveyor_pass)	//²àÑ¹¸´Î»
		{
			smp86xHandler[1]->setOutput(10, procFlag.conveyor_pass ? 1 : 0);	//Í¦°å
			_step1 = 73;
		}
		break;
	case 73:
		if (((ss[1].inputs>>15) & 0x1) == 0 || procFlag.conveyor_pass)	//Í¦°åµ½Î»
		{
			procFlag.conveyor_ready = (!procFlag.conveyor_pass);
			_step1 = 80;
			_step2 = 80;
		}
		break;
	}

	switch(_step2)
	{
	case 80:
		if (!procFlag.conveyor_ready)
		{
			smp86xHandler[1]->setOutput(8, 1);	//²àÑ¹
			smp86xHandler[1]->setOutput(9, 1);	//×èµ²
			smp86xHandler[1]->setOutput(10, 1);	//Í¦°å
			_step2 = 90;
		}
		break;
	case 90:
		if(procFlag.conveyor_pass)
		{
			smp86xHandler[1]->setOutput(0, 0);	//ÏÂÎ»Í¨Ñ¶
			_step2 = 100;
			break;
		}

		if (((ss[1].inputs>>14) & 0x1) == 0)	//Í¦°å¸´Î»
		{
			QSettings settings;
			int v1 = settings.value("Conveyor/speed_9", 1000).toInt();
			int v2 = settings.value("Conveyor/speed_10", 5000).toInt();
			int v3 = settings.value("Conveyor/speed_11", 500).toInt();
			smp86xHandler[1]->start(1, v1, -v2, v3/1000.0);	// Æô¶¯µç»ú2
			smp86xHandler[1]->setOutput(0, 0);	//ÏÂÎ»Í¨Ñ¶
			_step2 = 100;
		}
		break;
	case 100:
		if(((ss[1].inputs>>7) & 0x1) == 0 && _step1 == 80)
			_step1 = 0;

		if (((ss[1].inputs>>2) & 0x1) == 1 && ((ss[1].inputs>>7) & 0x1) == 0)	//ÏÂÎ»Í¨ÐÅ,³öÁÏ¸ÐÓ¦
		{
			elapsed += elapsedTimer.elapsed();
			elapsedTimer.invalidate();
			smp86xHandler[1]->stop(1);
			_step2 = 110;
		}
		if (((ss[1].inputs>>2) & 0x1) == 0 && ((ss[1].inputs>>7) & 0x1) == 0)	//ÏÂÎ»Í¨ÐÅ,³öÁÏ¸ÐÓ¦
		{
			elapsed += elapsedTimer.elapsed();
			elapsedTimer.invalidate();
			smp86xHandler[1]->stop(1);
			_step2 = 120;
		}
		break;
	case 110:
		if (((ss[1].inputs>>7) & 0x1) == 1)
		{
			_step2 = 0;
		}
		if (((ss[1].inputs>>2) & 0x1) == 0 && ((ss[1].inputs>>7) & 0x1) == 0)	//ÏÂÎ»Í¨ÐÅ,³öÁÏ¸ÐÓ¦
		{
			QSettings settings;
			int v1 = settings.value("Conveyor/speed_9", 1000).toInt();
			int v2 = settings.value("Conveyor/speed_10", 5000).toInt();
			int v3 = settings.value("Conveyor/speed_11", 500).toInt();
			smp86xHandler[1]->start(1, v1, -v2, v3/1000.0);	// Æô¶¯µç»ú2
			_step2 = 120;
		}
		break;
	case 120:
		if (((ss[1].inputs>>7) & 0x1) == 1)	//³öÁÏ¸ÐÓ¦
		{
			time.restart();
			_step2 = 130;
		}
		break;
	case 130:
		if(time.elapsed() < 500)
			break;

		smp86xHandler[1]->stop(1);
		_step2 = 0;
		break;
	}
}
#elif defined _OLD_VERSION
void PrintMark::runConveyor(SMP86X_STATUS ss[])
{
	QSettings settings;
	static int _step1 = 0, _step2 = 0;
	static QTime time1, time2, timeIn, timeOut, timeWork;
	if(!procFlag.conveyor_start && !procFlag.conveyor_pass)
	{
		_step1 = 0;
		_step2 = 0;
		return;
	}
 	if (_step2 > 10 && _step2 < 80)
 	{
 		timeRecord->setTime(2, timeWork.elapsed());
 		labelElapsed->setText(QString("Cycle Time: %1s").arg(timeWork.elapsed() / 1000.0, 0, 'f', 1));
 	}

	int v1 = settings.value("Conveyor/speed_0", 1000).toInt();
	int v2 = settings.value("Conveyor/speed_1", 5000).toInt();
	int v3 = settings.value("Conveyor/speed_2", 500).toInt();

 	switch (_step1)
 	{
 	case 0:
		if (((ss[0].inputs >> 18) & 0x1) == 1)
		{
			_step1 = 10;
		}
 		break;
 	case 10:
		smp86xHandler[0]->setOutput(1, 0);	// ¸øÉÏÎ»»úÐÅºÅ
		timeIn.restart();
		_step1 = 11;
		break;
 	case 11:
 		if (((ss[0].inputs >> 10) & 0x1) == 0 )	       // ½ø°åÓÐÐÅºÅ,ÓÐ°å½øÀ´
 		{	
			smp86xHandler[0]->setOutput(0, 1);				// ¹ØÉÏÎ»»úÐÅºÅ
			smp86xHandler[0]->setOutput(12, 0);				// Æô¶¯µç»ú1
 			//smp86xHandler[1]->start(1, v1, -v2, v3 / 1000.0);		
			addMessage(QString::fromUtf16(L"conveyor1 move!%1").arg(_step1), Qt::blue);
 			_step1 = 12;
			time1.restart();
 			break;
 		}
 		break;
	case 12:
		if (time1.elapsed()<100)
		{
			break;
		}
		_step1 = 13;
		break;
 	case 13:
		if (((ss[0].inputs >> 18) & 0x1) == 0)	// ´æ°å¸ÐÓ¦µ½°å
		{
			smp86xHandler[0]->setOutput(12, 1);				// stopµç»ú1
			//smp86xHandler[1]->stop(1);
			addMessage(QString::fromUtf16(L"conveyor1 stop!%1").arg(_step1), Qt::blue);
			_step1 = 16;
		}
		break;
 	case 16:
 		if (((ss[0].inputs >> 18) & 0x1) == 1)	// °åÀë¿ª´æ°å¸ÐÓ¦
 			break;
 		_step1 = 0;
// 		smp86xHandler[1]->stop(1);
		timeRecord->setTime(0, timeIn.elapsed());      //Ç°°åµÈ´ýÊ±¼ä
		break;
// 	case 20:
// 		if (((ss[0].inputs >> 11) & 0x1) == 0)	
// 		{
// 			_step1 = 30;
// 		}
// 		break;
//  	case 30:
//  		time2.restart();
//  		_step1 = 55;
//  		break;
//  	case 55:
//  		if (time2.elapsed() < dalay_broad)
//  			break;
//  		smp86xHandler[1]->stop(2);
//  		_step1 = 60;
//  		break;
//  	case 60:
//  		//wait for _strp2 finished
//  		if(_step2 == 0)
//  		_step1 = 0;
//  		break;
 	}

	switch(_step2)
	{
	case 0:
 		smp86xHandler[0]->setOutput(3, procFlag.conveyor_pass ? 1 : 0);	//×èµ²
		_step2 = 150;
		break;
	case 150:
		if (((ss[0].inputs >> 11) & 0x1) == 0)
		{
			_step2 = 10;
			break;
		}
		_step2 = 1;
		break;
	case 1:
		if (((ss[0].inputs >> 18) & 0x1) == 0 && _step1 == 0)
		{
			smp86xHandler[0]->setOutput(12, 0);				// Æô¶¯µç»ú1
			//smp86xHandler[1]->start(1, v1, -v2, v3 / 1000.0);     // Æô¶¯µç»ú1
			_step2 = 160;
			time2.restart();
		}
		break;
	case 160:
		if (time2.elapsed()<100)
		{
			break;
		}
		smp86xHandler[0]->setOutput(14, 0);				// Æô¶¯µç»ú2
		//smp86xHandler[1]->start(2, v1, -v2, v3 / 1000.0);     // Æô¶¯µç»ú2
		_step2 = 2;
		break;
	case 2:
		if (((ss[0].inputs >> 18) & 0x1) == 1 )
		{
			if (((ss[0].inputs >> 10) & 0x1) == 1)  //ÅÐ¶ÏÊÇ·ñÒÑ¾­Èë°å£¬Èç¹ûÈë°åÔò²»Í£Ö¹´«ËÍ´ø
			{
				smp86xHandler[0]->setOutput(12, 1);				// stopµç»ú1
				//smp86xHandler[1]->stop(1);
				addMessage(QString::fromUtf16(L"conveyor1 stop! _step2 %1").arg(_step2), Qt::blue);
			}
			_step2 = 3;
		}
		break;
	case 3:
		if(((ss[0].inputs>>11) & 0x1) == 0 )    //µ½Î»¸ÐÓ¦
		{
			time2.restart();
			_step2 = 4;
		}
		break;
	case 4:
		if (time2.elapsed() < dalay_broad)
			break;
		smp86xHandler[0]->setOutput(14, 1);				// stopµç»ú2
		//smp86xHandler[1]->stop(2);
		_step2 = 10;
		break;
	case 10:
		timeWork.restart();
		if(procFlag.conveyor_pass)
		{
			smp86xHandler[1]->setOutput(0, 0);	//ÏÂÎ»Í¨Ñ¶
			_step2 = 70;
			break;
		}
		_step2 = 20;
		break;
	case 20:
		time2.restart();
		smp86xHandler[0]->setOutput(5, procFlag.conveyor_pass ? 1 : 0);	   //Í¦°å
		_step2 = 21;
		break;
	case 21:
		if (time2.elapsed()>3000)
		{
			addMessage(QString::fromUtf16(L"Í¦°å³¬3ÃëÃ»µ½Î»"), Qt::red);
		}
		if (((ss[0].inputs >> 16) & 0x1) == 0 || procFlag.conveyor_pass)	//Í¦°åµ½Î»
		{
			_step2 = 30;
		}
		break;
	case 30:
		time2.restart();
		smp86xHandler[0]->setOutput(4, procFlag.conveyor_pass ? 1 : 0);	   //Ñ¹°å
		_step2 = 40;
		break;
	case 40:
		if (time2.elapsed() > 3000)
		{
			addMessage(QString::fromUtf16(L"Ñ¹°å³¬3ÃëÃ»µ½Î»"), Qt::red);
		}
		if (((ss[0].inputs >> 15) & 0x1) == 0 || procFlag.conveyor_pass)   //Ñ¹°åµ½Î»
		{
			_step2 = 50;
		}
		break;
	case 50:
		procFlag.conveyor_ready = (procFlag.conveyor_pass ? false : true);
		_step2 = 60;
		break;
	case 60:
		    //ÕâÊÇ¿ªÊ¼ÅçÂë
		if(procFlag.conveyor_ready)
			break;
		if (ui->checkBox_8->isChecked())
		{
			procFlag.conveyor_ready = (procFlag.conveyor_pass ? false : true);
			break;
		}
		_step2 = 61;
		break;
	case 61:
		smp86xHandler[0]->setOutput(3, 1);	//×èµ²
		smp86xHandler[0]->setOutput(4, 1);	//Ñ¹°å
		_step2 = 62;
		break;
	case 62:
		time2.restart();
		_step2 = 63;
		break;
	case 63:
		if (time2.elapsed()<200)
		{
			break;
		}
		smp86xHandler[0]->setOutput(5, 1);	//Í¦°å
		_step2 = 64;
		break;
	case 64:
		if (((ss[0].inputs >> 17) & 0x1) == 0)
		{
			_step2 = 65;
		}
		break;
	case 65:
		if (((ss[0].inputs >> 14) & 0x1) == 0)
		{
			_step2 = 70;
			smp86xHandler[0]->setOutput(0, 0);	//ÏÂÎ»Í¨Ñ¶
		}
		break;
	case 70:
		smp86xHandler[0]->setOutput(14, 0);				// Æô¶¯µç»ú2
		smp86xHandler[0]->setOutput(16, 0);				// Æô¶¯µç»ú3
// 		smp86xHandler[1]->start(2, v1, -v2, v3 / 1000.0);     // Æô¶¯µç»ú2
// 		smp86xHandler[1]->start(3, v1, -v2, v3 / 1000.0);     // Æô¶¯µç»ú3
		timeOut.restart();
		_step2 = 71;
		break;
	case 71:
		if (((ss[0].inputs >> 11) & 0x1) == 1)
		{
			_step2 = 80;
		}
		break;
	case 80:
		if (((ss[0].inputs>>12) & 0x1) == 0)	//ÏÂÎ»Í¨ÐÅ,³öÁÏ¸ÐÓ¦
		{
			smp86xHandler[0]->setOutput(14, 1);				// stopµç»ú2
			//smp86xHandler[1]->stop(2);
			_step2 = 81;
		}
		break;
	case 81:
		if (((ss[0].inputs >> 12) & 0x1) == 1)
		{
			smp86xHandler[0]->setOutput(16, 1);				// stopµç»ú3
			//smp86xHandler[1]->stop(3);
			timeRecord->setTime(1, timeOut.elapsed());
			_step2 = 0;
		}
		break;
// 	case 110:
// 		timeRecord->setTime(1, timeOut.elapsed());
// 		if (((ss[1].inputs>>7) & 0x1) == 1)
// 		{
// 			waitForDownChain += qMax(0, timeOut.elapsed()-inteval) ;
// 			_step2 = 0;
// 		}
// 		if (((ss[1].inputs>>2) & 0x1) == 0 && ((ss[1].inputs>>7) & 0x1) == 0)	//ÏÂÎ»Í¨ÐÅ,³öÁÏ¸ÐÓ¦
// 		{
// 			QSettings settings;
// 			int v1 = settings.value("Conveyor/speed_9", 1000).toInt();
// 			int v2 = settings.value("Conveyor/speed_10", 5000).toInt();
// 			int v3 = settings.value("Conveyor/speed_11", 500).toInt();
// 			smp86xHandler[1]->start(0, v1, v2, v3/1000.0);	// Æô¶¯µç»ú2
// 			waitForDownChain += qMax(0, timeOut.elapsed()-inteval) ;
// 			_step2 = 120;
// 		}
// 		break;
// 	case 120:
// 		if (((ss[1].inputs>>7) & 0x1) == 0)	//³öÁÏ¸ÐÓ¦
// 			break;
// 		_step2 = 125;
// 	case 125:
// 		if (((ss[1].inputs>>7) & 0x1) == 1)	//³öÁÏ¸ÐÓ¦
// 		{
// 			time1.restart();
// 			_step2 = 130;
// 		}
// 		break;
// 	case 130:
// 		if (time1.elapsed() < QSettings().value("Delay/outlet", 30).toInt())
// 			break;
// 
// 		smp86xHandler[1]->stop(0);
// 		_step2 = 0;
// 		break;
// 		//Í¬½øÍ¬³ö²½Öè
// 	case 200:
// 		if (((ss[1].inputs >> 4) & 0x1) == 1)
// 			break;
// 		_step2 = 210;
// 	case 210:
// 		if (((ss[1].inputs >> 4) & 0x1) == 0)
// 			break;
// 		smp86xHandler[1]->stop(0);
// 		_step2 = 0;
 	}
}
#else
void PrintMark::runConveyor(SMP86X_STATUS ss[])
{
	static int _step1 = 0, _step2 = 0, _step3 = 0;;
	static QTime time1, time2, time3, timeIn, timeOut, timeWork;
	if(!procFlag.conveyor_start && !procFlag.conveyor_pass)
	{
		_step1 = 0;
		_step2 = 0;
		_step3 = 0;
		return;
	}

	if (_step2 > 10 && _step2 < 90)
	{
		timeRecord->setTime(2, timeWork.elapsed());
		labelElapsed->setText(QString("Cycle Time: %1s").arg(timeWork.elapsed() / 1000.0, 0, 'f', 1));
	}

	switch (_step1)
	{
	case 0:
		if (((ss[1].inputs >> 20) & 0x1) == 0)	//ÖÐ¶ÎÓÐ°å
		{
			_step1 = 30;
			break;
		}

		smp86xHandler[0]->setOutput(17, 0);	// ¸øÉÏÎ»»úÐÅºÅ
		timeIn.restart();
		_step1 = 10;
		break;
	case 10:
		timeRecord->setTime(0, timeIn.elapsed());
		if (((ss[1].inputs >> 17) & 0x1) == 0 || ((ss[1].inputs >> 19) & 0x1) == 0)	// ÉÏÎ»»úÓÐÐÅºÅ,ÓÐ°å½øÀ´
		{
			smp86xHandler[0]->setOutput(17, 1);				// ¹ØÉÏÎ»»úÐÅºÅ
			smp86xHandler[0]->setOutput(23, 0);	// Æô¶¯µç»ú1
			waitForUpChain += qMax(0, timeIn.elapsed() - inteval);
			_step1 = 15;
			break;
		}

		if (((ss[1].inputs >> 20) & 0x1) == 0)	//ÒÑ¾­ÓÐ°åÔÚÖÐ¶Î
		{
			_step1 = 30;
			waitForUpChain += qMax(0, timeIn.elapsed() - inteval);
			//smp86xHandler[1]->setOutput(1, 1);	// ¹ØÉÏÎ»»úÐÅºÅ
			break;
		}
		smp86xHandler[0]->setOutput(23, 1);	// Í£µç»ú1
		break;
	case 15:
		_step1 = 20;
	case 20:
		//smp86xHandler[1]->setOutput(1, 1);				// ¹ØÉÏÎ»»úÐÅºÅ
		if (((ss[1].inputs >> 20) & 0x1) == 1)	// °å½øµ½µÚ¶þ¶Î
			break;
		smp86xHandler[0]->setOutput(23, 1);	// Í£µç»ú1
		_step1 = 30;
		return;
	case 30:
		if (((ss[1].inputs >> 20) & 0x1) == 0)
			break;
		time2.restart();
		_step1 = 55;
		break;
	case 55:
		if (time2.elapsed() < 100)
			break;
		//if (((ss[1].inputs >> 6) & 0x1) == 1)
		//	break;

		smp86xHandler[0]->setOutput(23, 1);	// Í£µç»ú1
		_step1 = 60;
		break;
	case 60:
		_step1 = 0;
		break;
	}

	switch(_step2)
	{
	case 0:
		if (((ss[1].inputs>>21) & 0x1) == 0 && procFlag.conveyor_pass)
		{
			procFlag.conveyor_ready = 0;
			_step2 = 60;
			break;
		}

		if (((ss[1].inputs>>21) & 0x1) == 0 && ((ss[1].inputs>>25) & 0x1) == 0)
		{
			procFlag.conveyor_ready = 0;
			_step2 = 60;
			break;
		}

		if (((ss[1].inputs>>21) & 0x1) == 0 && (((ss[1].inputs>>24) & 0x1) == 0 || procFlag.conveyor_pass))
		{
			procFlag.conveyor_ready = 0;
			_step2 = 70;
			break;
		}

		if(((ss[1].inputs>>21) & 0x1) == 1 && ((ss[1].inputs>>24) & 0x1) == 0)
		{
			smp86xHandler[0]->setOutput(22, procFlag.conveyor_pass ? 1 : 0);	//×èµ²
			_step2 = 10;
			break;
		}
		break;
	case 10:
		if((((ss[1].inputs>>20) & 0x1) == 0) && (_step1 == 30) && (((ss[1].inputs>>27) & 0x1) == 0 || procFlag.conveyor_pass))
		{
			smp86xHandler[0]->setOutput(23, 0);	// Æô¶¯µç»ú1
			smp86xHandler[0]->setOutput(24, 0);	// Æô¶¯µç»ú2
			timeWork.restart();
			_step2 = 20;
			break;
		}
		break;
	case 20:
		if(procFlag.conveyor_pass)
		{
			_step2 = 80;
			break;
		}
		if(((ss[1].inputs>>21) & 0x1) == 0)
		{
			time1.restart();
			_step2 = 30;
		}
		break;
	case 30:
		if(time1.elapsed() < 100)
			break;

		smp86xHandler[0]->setOutput(24, 1);	// Æô¶¯µç»ú2
		smp86xHandler[0]->setOutput(21, procFlag.conveyor_pass ? 1 : 0);	//Í¦°å
		_step2 = 40;
		break;
	case 40:
		if (((ss[1].inputs>>25) & 0x1) == 0 || procFlag.conveyor_pass)	//Í¦°åµ½Î»
		{
			time1.restart();
			_step2 = 50;
		}
		break;
	case 50:
		if(time1.elapsed() < 100)
			break;

		procFlag.conveyor_ready = (procFlag.conveyor_pass ? false : true);
		_step2 = 60;
		break;
	case 60:
		if(procFlag.conveyor_ready)
			break;

		smp86xHandler[0]->setOutput(22, 1);	//×èµ²
		smp86xHandler[0]->setOutput(21, 1);	//Í¦°å
		_step2 = 70;
		break;
	case 70:
		if (((ss[1].inputs>>24) & 0x1) == 0 && ((ss[1].inputs>>26) & 0x1) == 0)	//Í¦°å¸´Î»£¬×èµ²¸´Î»
		{
			_step2 = 80;
		}
		break;
	case 80:
		if (((ss[1].inputs >> 23) & 0x1) == 0)
			break;
		smp86xHandler[0]->setOutput(24, 0);	// Æô¶¯µç»ú2
		smp86xHandler[0]->setOutput(25, 0);	// Æô¶¯µç»ú3
		_step2 = 85;
	case 85:
		if (((ss[1].inputs >> 22) & 0x1) == 1)
			break;

		_step2 = 90;
	case 90:
		if (((ss[1].inputs >> 22) & 0x1) == 0)
			break;

		_step2 = 0;
		smp86xHandler[0]->setOutput(24, 1);	// Í£µç»ú2
	}

	switch (_step3)
	{
	case 0:
		if (((ss[1].inputs >> 23) & 0x1) == 0)
		{
			_step3 = 40;
			break;
		}
		if (((ss[1].inputs >> 21) & 0x1) == 0)
		{
			smp86xHandler[0]->setOutput(16, 0);	// ÏÂÎ»»úÍ¨Ñ¶
			_step3 = 10;
		}
		break;
	case 10:
		if (((ss[1].inputs >> 23) & 0x1) == 1)
			break;
		
		_step3 = 30;
		if (((ss[1].inputs >> 16) & 0x1) == 1)
		{
			smp86xHandler[0]->setOutput(25, 1);	// Í£µç»ú3
			_step3 = 20;
		}
		break;
	case 20:
		if (((ss[1].inputs >> 23) & 0x1) == 1)
			_step3 = 0;
		if (((ss[1].inputs >> 16) & 0x1) == 1)
			break;
		smp86xHandler[0]->setOutput(25, 0);	// Æô¶¯µç»ú3
		_step3 = 30;
	case 30:
		if (((ss[1].inputs >> 23) & 0x1) == 0)
			break;
		_step3 = 40;
		time3.restart();
	case 40:
		if (time3.elapsed() < 100)
			break;
		smp86xHandler[0]->setOutput(25, 1);	// Í£µç»ú3
		_step3 = 0;
	}
}
#endif // 0

void PrintMark::runHoming(SMP86X_STATUS ss[])
{
	static int _step = 0;
	uchar data[4] = {0,};
	if (!procFlag.homing)
	{
		_step = 0;
		return;
	}

	if(isRunning(ss[0]))
		return;

	switch(_step)
	{
	case 0:
		//smp86xHandler[0]->home(2);
		procFlag.real_time = true;
		_step = 10;
		break;
	case 10:
		smp86xHandler[0]->home(0);
 		smp86xHandler[0]->home(1);
 		smp86xHandler[0]->home(2);
		procFlag.real_time = true;
		_step = 20;
		break;
	case 20:
#ifdef _OLD_VERSION
		smp86xHandler[0]->start(2, QSettings().value("Print/u", 0).toDouble()/pulseEquivalent[3], speedValue[9], speedValue[10], speedValue[11]/1000.0);
#endif // _OLD_VERSION
		_step = 30;
		break;
	case 30:
		procFlag.homing = false;
		smp86xHandler[1]->setOutput(8, 1);
		smp86xHandler[1]->setOutput(9, 1);
		//smp86xHandler[0]->writeRawBits(0x28, 4, data);
		_step = 0;
		break;
	}
}

#if 0		// Ã¿¿´Ò»¸ö»µµãÅçÒ»¸öÂë
void PrintMark::runPrinting(SMP86X_STATUS ss[])
{
	static int _step = 0, _index = 0;
	static QTime time;
	if(!procFlag.printing_start)
	{
		_step = 0; _index = 0;
		return;
	}
	if(procFlag.printing_pause)
		return;

	if(isRunning(ss[0]))
		return;

	QSettings settings;
	QVector3D markPos[2];
	QTransform trans;
	double markDist1, markDist2, angle;
	int dist, dist1, dist2;
	QString text;
	QByteArray buff;

	double markDistDiff = settings.value("mark_dist_diff", 3).toDouble();
	//double print_z = settings.value("Print/z", 0).toDouble();
	//double print_u = settings.value("Print/u", 0).toDouble();
	int delay_snap = settings.value("Delay/snap", 50).toInt();
	int delay_print = settings.value("Print/delay", 100).toInt();

	float x, y, z, u;

	switch(_step)
	{
	case 0:
		if(markData[0].firstPos.isNull() || markData[1].firstPos.isNull())
		{
		}
		else
		{
			markPos[0].setX(settings.value("Position/mark1_x", 0).toDouble());
			markPos[0].setY(settings.value("Position/mark1_y", 0).toDouble());
			markPos[0].setZ(settings.value("Position/mark1_z", 0).toDouble());
			smp86xHandler[0]->start(0, 1, (markPos[0].x()/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (markPos[0].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
			//smp86xHandler[0]->start(1, (markPos[0].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			smp86xHandler[0]->start(2, (markPos[0].z()/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		}
		procFlag.real_time = true;
		_step = 10;
		break;
	case 10:
		if(!procFlag.conveyor_ready)
			break;

		if(markData[0].firstPos.isNull() || markData[1].firstPos.isNull())
		{
			for (int i=0; i<ui->tableWidget->rowCount(); i++)
			{
				ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
				x = ui->tableWidget->item(i, 1)->text().toDouble();
				y = ui->tableWidget->item(i, 2)->text().toDouble();
				ui->tableWidget->item(i, 3)->setText(QString("%1").arg(x, 0, 'f', 3));
				ui->tableWidget->item(i, 4)->setText(QString("%1").arg(y, 0, 'f', 3));
			}
			for (int i=0; i<ui->tableWidget_2->rowCount() && ui->checkBox->isChecked(); i++)
			{
				ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(i, 0));
				x = ui->tableWidget_2->item(i, 1)->text().toDouble();
				y = ui->tableWidget_2->item(i, 2)->text().toDouble();
				ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(x, 0, 'f', 3));
				ui->tableWidget_2->item(i, 4)->setText(QString("%1").arg(y, 0, 'f', 3));
			}
			_step = 60;
			_index = 0;
			break;
		}

		smp86xHandler[0]->setPWM(0, ui->horizontalSlider->value());
		time.restart();
		_step = 20;
		break;
	case 20:
		if(time.elapsed() < delay_snap)
			break;
		if(!_visionPos(x, y, u))
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼1Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			break;
		}

		markData[0].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
		markData[0].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);

		markPos[1].setX(settings.value("Position/mark2_x", 0).toDouble());
		markPos[1].setY(settings.value("Position/mark2_y", 0).toDouble());
		markPos[1].setZ(settings.value("Position/mark2_z", 0).toDouble());
		smp86xHandler[0]->start(0, 1, (markPos[1].x()/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (markPos[1].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
		//smp86xHandler[0]->start(1, (markPos[1].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
		smp86xHandler[0]->start(2, (markPos[1].z()/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		procFlag.real_time = true;
		_step = 30;
		break;
	case 30:
		time.restart();
		_step = 40;
		break;
	case 40:
		if(time.elapsed() < delay_snap)
			break;
		if(!_visionPos(x, y, u))
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼2Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			break;
		}

		markData[1].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
		markData[1].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
		_step = 50;
		break;
	case 50:
		markDist1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).length();
		markDist2 = QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()).length();
		if(abs(markDist2 - markDist1) > markDistDiff)
		{
			//QMessageBox::information(this, QString::fromUtf16(L"ÐÅÏ¢"), QString::fromUtf16(L"»ù×¼µã¾àÀëÓÐÎó!"));
			addMessage(QString::fromUtf16(L"»ù×¼µã¾àÀëÓÐÎó!"), Qt::red);
			on_pushButton_18_clicked();
			break;
		}

		if(!vector_to_rigid(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF(), 
			markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF(), trans))
		{
			addMessage(QString::fromUtf16(L"×ø±ê×ª»»Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			break;
		}

		for (int i=0; i<ui->tableWidget->rowCount(); i++)
		{
			ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
			x = ui->tableWidget->item(i, 1)->text().toDouble();
			y = ui->tableWidget->item(i, 2)->text().toDouble();
			QPointF pos = trans.map(QPointF(x, y));
			ui->tableWidget->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
			ui->tableWidget->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
		}

		for (int i=0; i<ui->tableWidget_2->rowCount() && ui->checkBox->isChecked(); i++)
		{
			ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(i, 0));
			x = ui->tableWidget_2->item(i, 1)->text().toDouble();
			y = ui->tableWidget_2->item(i, 2)->text().toDouble();
			QPointF pos = trans.map(QPointF(x, y));
			ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
			ui->tableWidget_2->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
		}
		_step = 60;
		_index = 0;
		break;
	case 60:
		if (ui->checkBox->isChecked() && ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		{
			x = ui->tableWidget_2->item(_index, 3)->text().toDouble();
			y = ui->tableWidget_2->item(_index, 4)->text().toDouble();
			z = settings.value("Position/mark1_z", 0).toDouble();//settings.value("Print/z", 0).toDouble();
			smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
			//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
			procFlag.real_time = true;
			_step = 70;
			break;
		}
		else if (ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		{
			//ui->tableWidget_2->item(_index, 0)->setCheckState(Qt::Checked);
			_step = 90;
			break;
		}

		if(++_index < ui->tableWidget->rowCount())
			break;

		_step = 120;
		break;
	case 70:
		time.restart();
		_step = 80;
		break;
	case 80:
		if(time.elapsed() < delay_snap)
			break;

		ui->tableWidget_2->item(_index, 0)->setCheckState(visionValid() ? Qt::Unchecked : Qt::Checked);
#if 0
		if(++_index < ui->tableWidget_2->rowCount())
		{
			_step = 60;
			break;
		}

		_index = 0;
#endif // 0
		_step = 90;
		break;
	case 90:
		if((!ui->checkBox->isChecked() || 
			ui->tableWidget_2->item(_index, 0)->checkState() == Qt::Unchecked)
			&& ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		{
			// PCBÐý×ª½Ç¶È
			double u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			double cx = settings.value("Offset/center_x", "0.000").toDouble();
			double cy = settings.value("Offset/center_y", "0.000").toDouble();
			double dx = settings.value("Offset/ofs_x", "0.000").toDouble();
			double dy = settings.value("Offset/ofs_y", "0.000").toDouble();
			double du = settings.value("Offset/ofs_u", "0.000").toDouble();
			QPointF p = QTransform().rotate(u1).map(QPointF(cx-dx, cy-dy));
			double ax = p.x() - (cx-dx);
			double ay = p.y() - (cy-dy);
			x = ui->tableWidget->item(_index, 3)->text().toDouble() + ax + dx;
			y = ui->tableWidget->item(_index, 4)->text().toDouble() + ay + dy;
			z = settings.value("Print/z", 0).toDouble();
			u = settings.value("Print/u", 0).toDouble()/*+u1*/;
			smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
			//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
			smp86xHandler[1]->start(3, (u/pulseEquivalent[3] - ss[1].axis_status[3].logicPos), speedValue[9], speedValue[10], speedValue[11]/1000.0);
			procFlag.real_time = true;

			QByteArray next = settings.value("Code/next", "0001").toString().toLatin1();
			QByteArray prefix = settings.value("Code/prefix", "F0P54S").toString().toLatin1();
			QByteArray subfix = settings.value("Code/subfix", "FY9Y9Z1").toString().toLatin1();
			if (next == "YYYY")
			{
				addMessage(QString::fromUtf16(L"¶þÎ¬ÂëÐòÁÐÒÑÓÃÍê!"), Qt::red);
				on_pushButton_18_clicked();
				procFlag.code_empty_err = true;
				break;
			}
			text = ui->lineEdit_2->text();
			buff = QString("\x1bOE%1%2\x04").arg(text.size(), 4, 10, QChar('0')).arg(text).toLatin1();
			device->write(buff);
			_step = 100;
			break;
		}

		_step = 60;
		break;
	case 100:
		smp86xHandler[0]->setOutput(0, ui->checkBox_2->isChecked() ? 0 : 1);
		smp86xHandler[0]->setOutput(1, ui->checkBox_3->isChecked() ? 0 : 1);
		smp86xHandler[0]->setOutput(2, 0);
		_step = 101;
		time.restart();
		break;
	case 101:
		if(time.elapsed() < delay_print)
			break;
		{
			double u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			double division = settings.value("Print/division", 40).toDouble();
			dist = settings.value("Print/dist", 10000).toInt();
			angle = settings.value("Print/angle", 0).toDouble()+u1;
			dist1 = dist*cos(angle*M_PI/180);
			dist2 = dist*sin(angle*M_PI/180);
			//smp86xHandler[0]->start(0, 1, dist1, dist2, speedValue[12], speedValue[13], speedValue[14]/1000.0);
			smp86xHandler[0]->start(0, 3, dist, dist/division, speedValue[12], speedValue[13], speedValue[14]/1000.0);
			procFlag.real_time = true;
			_step = 110;

			QByteArray next = settings.value("Code/next", "0001").toString().toLatin1();
			QByteArray prefix = settings.value("Code/prefix", "F0P54S").toString().toLatin1();
			QByteArray subfix = settings.value("Code/subfix", "FY9Y9Z1").toString().toLatin1();
			next = nextCode(next);
			settings.setValue("Code/next", QString::fromLatin1(next));
			//ui->lineEdit_2->setText(prefix+next+subfix);
		}
		break;
	case 110:
		smp86xHandler[0]->setOutput(2, 1);

		if(++_index < ui->tableWidget->rowCount())
		{
			_step = 60;
			break;
		}

		_step = 120;
		break;
	case 120:
		smp86xHandler[0]->start(2, (0/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		procFlag.real_time = true;
		_step = 130;
		break;
	case 130:
		procFlag.scancode_start = true;
		_step = 140;
		break;
	case 140:
		if(procFlag.scancode_start)
			break;

		procFlag.conveyor_ready = false;
		_step = 0;
		break;
	}
}
#else		// ÏÈ¿´È«»µµãÔÙÅçÂë
void PrintMark::runPrinting(SMP86X_STATUS ss[])
{
	static int _step = 0, _index = 0, order = 0 , sumNumber = 1;
	static float x, y, z, u ,flagSame;
	static float dx1, dy1;
	static QTime time;
	static QMutex _mutex;
	if (!_mutex.tryLock())
		return;

	_mutex.unlock();
	QMutexLocker l(&_mutex);

	if(!procFlag.printing_start)
	{
		_step = 0; _index = 0; order = 0; 
		return;
	}
	if(procFlag.printing_pause)
		return;

	QSettings settings;
	bool door_stop = settings.value("door_stop", false).toBool();
	if (door_stop && ((((ss[0].inputs>>7) & 0x1) == 1) || (((ss[0].inputs>>8) & 0x1) == 1)))
	{
		procFlag.printing_start = false;
		procFlag.scancode_start = false;
		smp86xHandler[0]->stopAll();
		addMessage(QString::fromUtf16(L"ÒÑÍ£Ö¹! Ô­Òò: ÃÅ±»¿ªÆô"), Qt::red);
		sigStat.alarm = 0;
		return;
	}

	if(isRunning(ss[0]))
		return;

	QVector3D markPos[2];
	QTransform trans;
	double markDist1, markDist2, angle;
	int dist, dist1, dist2;
	QString text;
	QByteArray buff;
	QByteArray readCode;
	time_t t;

	double markDistDiff = settings.value("mark_dist_diff", 3).toDouble();
	//double print_z = settings.value("Print/z", 0).toDouble();
	//double print_u = settings.value("Print/u", 0).toDouble();
	int delay_mark = settings.value("Delay/mark", 100).toInt();
	int delay_badm = settings.value("Delay/badm", 100).toInt();
	int delay_code = settings.value("Delay/code", 100).toInt();
	int delay_print = settings.value("Print/delay", 100).toInt();
	int lastRow = ui->tableWidget->rowCount()-1;
	double speed = settings.value("Print/speed", 100).toInt()/100.0;
	flyprintf.enabled = 1;
	flyprintf.target = 2;
	flyprintf.pin = 2;

	bool vision_result;
	
	switch (_step)
	{
	case 0:
		if (markData[0].firstPos.isNull() || markData[1].firstPos.isNull())
		{
			addMessage(QString::fromUtf16(L"»ù×¼Êý¾Ý¿Õ"), Qt::darkYellow);
		}
		else
		{
			markPos[0].setX(settings.value("Position/mark1_x", 0).toDouble());
			markPos[0].setY(settings.value("Position/mark1_y", 0).toDouble());
			markPos[0].setZ(settings.value("Position/mark1_z", 0).toDouble());
			z = settings.value("Print/z", 0).toDouble();
			addMessage(QString::fromUtf16(L"»ù×¼1ÅÄÕÕÎ»ÖÃ"), Qt::darkCyan);
			smp86xHandler[0]->start(0, 1, (markPos[0].x() / pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (markPos[0].y() / pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
			//smp86xHandler[0]->start(1, (markPos[0].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		}
		procFlag.real_time = true;
		_step = 10;

		break;
	case 10:
		if (!procFlag.conveyor_ready)
		{
			break;
		}
#ifdef _OLD_VERSION
// 		if (settings.value("Code/enable", true).toBool())
// 		{
// 			buff = "\x1bP1001\x04";
// 			sendPrintData(device, buff);
// 		}
#endif // _OLD_VERSION
		for (int i = 0; i < ui->tableWidget->rowCount(); i++)
			for (int j = 0; j < ui->tableWidget->columnCount(); j++)
				ui->tableWidget->item(i, j)->setBackground(QBrush());
		if (markData[0].firstPos.isNull() || markData[1].firstPos.isNull())
		{
			double makeup_x = settings.value("Position/makeup_x", 0).toDouble();
			double makeup_y = settings.value("Position/makeup_y", 0).toDouble();
			for (int i = 0; i < ui->tableWidget->rowCount(); i++)
			{
				ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
				x = ui->tableWidget->item(i, 1)->text().toDouble();
				y = ui->tableWidget->item(i, 2)->text().toDouble();
				ui->tableWidget->item(i, 3)->setText(QString("%1").arg(x + makeup_x, 0, 'f', 3));
				ui->tableWidget->item(i, 4)->setText(QString("%1").arg(y + makeup_y, 0, 'f', 3));
				ui->tableWidget->item(i, 0)->setText(QString(""));
			}
			for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
			{
				ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(i, 0));
				x = ui->tableWidget_2->item(i, 1)->text().toDouble();
				y = ui->tableWidget_2->item(i, 2)->text().toDouble();
				ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(x, 0, 'f', 3));
				ui->tableWidget_2->item(i, 4)->setText(QString("%1").arg(y, 0, 'f', 3));
				ui->tableWidget_2->item(i, 0)->setCheckState(Qt::Unchecked);
			}
			for (int i = 0; i < ui->tableWidget_3->rowCount(); i++)
			{
				x = ui->tableWidget_3->item(i, 1)->text().toDouble();
				y = ui->tableWidget_3->item(i, 2)->text().toDouble();
				ui->tableWidget_3->item(i, 3)->setText(QString("%1").arg(x, 0, 'f', 3));
				ui->tableWidget_3->item(i, 4)->setText(QString("%1").arg(y, 0, 'f', 3));
			}
			//Çå»º´æ
			{
				if (!ui->checkBox_9->isChecked())
				{
					QByteArray device_data = QString("OE00002").toLatin1();
					QByteArray device_data2 = QString("OE00001").toLatin1();
					sendpre = sendInkData(device, device_data);
					sendpre2 = sendInkData(device, device_data2);
					if (!sendpre && !sendpre2)
						QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨½øÐÐ³õÊ¼»¯\n"), QString::fromUtf16(L"È·¶¨"));
					else
						addMessage(QString::fromUtf16(L"³õÊ¼»¯³É¹¦"), Qt::blue);
				}
			}
			_step = 55;
			_index = 0;
			break;
		}
		else
		{
			for (int i = 0; i < ui->tableWidget->rowCount(); i++)
			{
				ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
				ui->tableWidget->item(i, 0)->setText(QString(""));
				ui->tableWidget->item(i, 3)->setText(QString(""));
				ui->tableWidget->item(i, 4)->setText(QString(""));
			}
// 			for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
// 			{
// 				ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(i, 0));
// 				ui->tableWidget_2->item(i, 0)->setCheckState(Qt::Unchecked);
// 				ui->tableWidget_2->item(i, 3)->setText(QString(""));
// 				ui->tableWidget_2->item(i, 4)->setText(QString(""));
// 			}
// 			for (int i = 0; i < ui->tableWidget_3->rowCount(); i++)
// 			{
// 				ui->tableWidget_3->item(i, 3)->setText(QString(""));
// 				ui->tableWidget_3->item(i, 4)->setText(QString(""));
// 			}
		}
		//Çå»º´æ
		{
			if (!ui->checkBox_9->isChecked())
			{
				QByteArray device_data = QString("OE00002").toLatin1();
				QByteArray device_data2 = QString("OE00001").toLatin1();
				sendpre = sendInkData(device, device_data);
				sendpre2 = sendInkData(device, device_data2);
				if (!sendpre && !sendpre2)
					QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨½øÐÐ³õÊ¼»¯\n"), QString::fromUtf16(L"È·¶¨"));
				else
					addMessage(QString::fromUtf16(L"³õÊ¼»¯³É¹¦"), Qt::blue);
			}	
		}
		/*smp86xHandler[0]->setPWM(0, settings.value("Light/mark", 30).toInt()*255/100);*/
		time.restart();
		_step = 20;
		break;
	case 20:
		if (time.elapsed() < delay_mark)
			break;
		future = QtConcurrent::run([this]()->bool {return _visionPos(x, y, u, 0); });
		_step = 21;
		break;
	case 21:
		if (future.isRunning())
			break;
		vision_result = future.result();
		future = QFuture<bool>();
		if (!vision_result/*_visionPos(x, y, u)*/)
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼1Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			QString _station = settings.value("SFC/linename").toString();
			SaveTestData(_station + ";30;" + strEmployee + ";3;");
			int res = QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"»ñÈ¡»ù×¼1Ê§°Ü"), QMessageBox::Retry, QMessageBox::Abort);
			SaveTestData(_station + ";30;" + strEmployee + ";23;");
			sigStat.alarm = 1;
			switch (res)
			{
			case QMessageBox::Retry:
				procFlag.printing_pause = false;
				time.restart();
				_step = 20;
				return;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				break;
			}
			break;
		}

		markData[0].curntPos.setX(x + ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
		markData[0].curntPos.setY(y + ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
		addMessage(QString::fromUtf16(L"»ù×¼1: %1\t%2\t%3").arg(markData[0].curntPos.x(), 0, 'f', 3).arg(markData[0].curntPos.y(), 0, 'f', 3).arg(u, 0, 'f', 3));

		markPos[1].setX(settings.value("Position/mark2_x", 0).toDouble());
		markPos[1].setY(settings.value("Position/mark2_y", 0).toDouble());
		markPos[1].setZ(settings.value("Position/mark2_z", 0).toDouble());
		smp86xHandler[0]->start(0, 1, (markPos[1].x() / pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (markPos[1].y() / pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
		//smp86xHandler[0]->start(1, (markPos[1].y()/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
		//smp86xHandler[0]->start(2, (markPos[1].z()/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		procFlag.real_time = true;
		_step = 30;
		break;
	case 30:
		time.restart();
		_step = 40;
		break;
	case 40:
		if (time.elapsed() < delay_mark)
			break;
		future = QtConcurrent::run([this]()->bool {return _visionPos(x, y, u, 0); });
		_step = 41;
		break;
	case 41:
		if (future.isRunning())
			break;
		vision_result = future.result();
		future = QFuture<bool>();
		if (!vision_result/*_visionPos(x, y, u)*/)
			//if(!_visionPos(x, y, u))
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼2Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			QString _station = settings.value("SFC/linename").toString();
			SaveTestData(_station + ";30;" + strEmployee + ";3;");
			int res = QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"»ñÈ¡»ù×¼2Ê§°Ü"), QMessageBox::Retry, QMessageBox::Abort);
			SaveTestData(_station + ";30;" + strEmployee + ";23;");
			sigStat.alarm = 1;
			switch (res)
			{
			case QMessageBox::Retry:
				procFlag.printing_pause = false;
				_step = 40;
				time.restart();
				return;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				break;
			}
			break;
		}

		markData[1].curntPos.setX(x + ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
		markData[1].curntPos.setY(y + ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
		addMessage(QString::fromUtf16(L"»ù×¼2: %1\t%2\t%3").arg(markData[1].curntPos.x(), 0, 'f', 3).arg(markData[1].curntPos.y(), 0, 'f', 3).arg(u, 0, 'f', 3));
		_step = 50;
	case 50:
		markDist1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).length();
		markDist2 = QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()).length();
		addMessage(QString::fromUtf16(L"¾àÀë: %3/%4, ²î:%1/%2").arg(abs(markDist2 - markDist1), 0, 'f', 3).arg(QSettings().value("mark_dist_diff", 3).toDouble(), 0, 'f', 3)
			.arg(markDist2, 0, 'f', 3).arg(markDist1, 0, 'f', 3));
		if (abs(markDist2 - markDist1) > markDistDiff)
		{
			//QMessageBox::information(this, QString::fromUtf16(L"ÐÅÏ¢"), QString::fromUtf16(L"»ù×¼µã¾àÀëÓÐÎó!"));
			addMessage(QString::fromUtf16(L"»ù×¼µã¾àÀëÓÐÎó!"), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			QString _station = settings.value("SFC/linename").toString();
			SaveTestData(_station + ";30;" + strEmployee + ";3;");
			int res = QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"»ù×¼µã¾àÀëÓÐÎó"), QMessageBox::Retry, QMessageBox::Abort);
			SaveTestData(_station + ";30;" + strEmployee + ";23;");
			sigStat.alarm = 1;
			switch (res)
			{
			case QMessageBox::Retry:
				procFlag.printing_pause = false;
				_step = 0;
				return;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				break;
			}
			break;
		}

		if (!vector_to_rigid(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF(),
			markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF(), trans))
		{
			addMessage(QString::fromUtf16(L"×ø±ê×ª»»Ê§°Ü"), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			break;
		}

		if (true)
		{
			double makeup_x = settings.value("Position/makeup_x", 0).toDouble();
			double makeup_y = settings.value("Position/makeup_y", 0).toDouble();
			for (int i = 0; i < ui->tableWidget->rowCount(); i++)
			{
				x = ui->tableWidget->item(i, 1)->text().toDouble() + makeup_x;
				y = ui->tableWidget->item(i, 2)->text().toDouble() + makeup_y;
				QPointF pos = trans.map(QPointF(x, y));
				ui->tableWidget->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
				ui->tableWidget->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
			}
// 
// 			for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
// 			{
// 				x = ui->tableWidget_2->item(i, 1)->text().toDouble();
// 				y = ui->tableWidget_2->item(i, 2)->text().toDouble();
// 				QPointF pos = trans.map(QPointF(x, y));
// 				ui->tableWidget_2->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
// 				ui->tableWidget_2->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
// 			}
// 
// 			for (int i = 0; i < ui->tableWidget_3->rowCount(); i++)
// 			{
// 				x = ui->tableWidget_3->item(i, 1)->text().toDouble();
// 				y = ui->tableWidget_3->item(i, 2)->text().toDouble();
// 				QPointF pos = trans.map(QPointF(x, y));
// 				ui->tableWidget_3->item(i, 3)->setText(QString("%1").arg(pos.x(), 0, 'f', 3));
// 				ui->tableWidget_3->item(i, 4)->setText(QString("%1").arg(pos.y(), 0, 'f', 3));
// 			}
		}
		/*if (ui->checkBox->isChecked())*/
			//	smp86xHandler[0]->setPWM(0, settings.value("Light/badm", 30).toInt()*255/100);
		_step = 55;
		_index = 0;
		break;
	case 55:
		//send print code comment
		for (int i = 0; i < ui->tableWidget->rowCount(); i++)
		{
			if (ui->tableWidget->item(i,0)->checkState() == Qt::Unchecked)
				continue;
		_NEXT1:
			QString textModel = ui->tableWidget->item(i, 6)->text();
			curPrintf = ui->tableWidget->item(i, 6)->text().toInt() - 1;
			chushi = 1;
			updateStatistics();
			text = ui->lineEdit_2->text();
			_Database::check(text.toLatin1(), t);
			if (t != 0)
			{
				sigStat.alarm = 0;
				if (!ui->checkBox_7->isChecked())
				{
					goto FLAG3;
					sigStat.alarm = 1;
				}
				int res = QMessageBox::warning(this, QString::fromUtf16(L"·¢ÏÖÖØÂë"), QString::fromUtf16(L"%1\nµÄÉÏ´Î´òÓ¡Ê±¼äÎª:\n%2").arg(text).arg(ctime(&t)), QString::fromUtf16(L"ÏÂÒ»¸ö"), QString::fromUtf16(L"ÔÝÍ£"));
				sigStat.alarm = 1;
				switch (res)
				{
				case 0:
					updateStatistics();
					goto _NEXT1;
				case 1:
					procFlag.printing_pause = true;
					return;
				}
			}
		FLAG3:
			if (!ui->checkBox_9->isChecked())
			{
				QString Schangtext = QString("P1%1").arg(textModel);
				bool exit3 = sendInkData(device, Schangtext.toLatin1());
				if (!exit3)
				{
					QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨¸ü¸ÄÎÄ±¾\n"), QString::fromUtf16(L"È·¶¨"));
					procFlag.printing_pause = true;
					return;
				}
				bool exit2 = printfCurText();    //·¢ËÍÅçÓ¡Êý¾Ý
				if (!exit2)
				{
					return;
				}
				ui->tableWidget->item(i, 0)->setText(text);
			}
			addMessage(QString("send data times:%1").arg(i), Qt::blue);
			updateStatistics();
		}
		_step = 60;
		break;
	case 60:
		if (!ui->checkBox->isChecked())
		{
			_index = 0;
			_step = 85;
			break;
		}
		//	_step = 61;
		//case 61:
		if (ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		{
			x = ui->tableWidget_2->item(_index, 3)->text().toDouble();
			y = ui->tableWidget_2->item(_index, 4)->text().toDouble();
			z = settings.value("Print/z", 0).toDouble();
			smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
			//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
			procFlag.real_time = true;
			_step = 70;
			break;
		}
		//else if (ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		//{
		//	//ui->tableWidget_2->item(_index, 0)->setCheckState(Qt::Checked);
		//	_step = 90;
		//	break;
		//}

		if (++_index < ui->tableWidget->rowCount())
			break;

		_index = 0;
		_step = 85;
		break;
	case 70:
		time.restart();
		_step = 80;
		break;
	case 80:
		if (time.elapsed() < delay_badm)
			break;

		future = QtConcurrent::run([this]()->bool {return visionValid(); });
		_step = 81;
		break;
	case 81:
		if (future.isRunning())
			break;
		vision_result = future.result();
		ui->tableWidget_2->item(_index, 0)->setCheckState(/*visionValid()*/vision_result ? Qt::Unchecked : Qt::Checked);
		if (ui->comboBox->currentIndex() == 1 && vision_result)
		{
			future = QtConcurrent::run([this]()->bool {return _visionPos(x, y, u, 2); });
			_step = 82;
			break;
		}

		future = QFuture<bool>();
		if (++_index < ui->tableWidget_2->rowCount())
		{
			_step = 60;
			break;
		}

		_index = 0;
		_step = 85;
		break;
	case 82:
		if (future.isRunning())
			break;
		vision_result = future.result();
		if (!vision_result)
		{
			addMessage(QString::fromUtf16(L"°×ÓÍÇøÓò%1¶¨Î»Ê§°Ü").arg(_index + 1), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			QString _station = settings.value("SFC/linename").toString();
			SaveTestData(_station + ";30;" + strEmployee + ";3;");
			int res = QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"°×ÓÍÇøÓò%1¶¨Î»Ê§°Ü").arg(_index + 1), QString::fromUtf16(L"ÖØÊÔ"), QString::fromUtf16(L"Ìø¹ý"), QString::fromUtf16(L"Í£Ö¹"));
			SaveTestData(_station + ";30;" + strEmployee + ";23;");
			sigStat.alarm = 1;
			switch (res)
			{
			case 0:
				procFlag.printing_pause = false;
				future = QtConcurrent::run([this]()->bool {return _visionPos(x, y, u, 2); });
				return;
			case 1:
				procFlag.printing_pause = false;
				ui->tableWidget_2->item(_index, 0)->setCheckState(Qt::Checked);
				break;
			case 2:
				on_pushButton_5_clicked();
				return;
			}
		}
		x += ui->tableWidget->item(_index, 1)->text().toDouble();
		y += ui->tableWidget->item(_index, 2)->text().toDouble();
		ui->tableWidget->item(_index, 3)->setText(QString("%1").arg(x + ss[0].axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
		ui->tableWidget->item(_index, 4)->setText(QString("%1").arg(y + ss[0].axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
		future = QFuture<bool>();
		if (++_index < ui->tableWidget_2->rowCount())
		{
			_step = 60;
			break;
		}

		_index = 0;
		_step = 85;
		break;
	case 85:
		if (false && ui->actionSfc->isChecked())
		{
			QString msg;
			QString endpoint = settings.value("Sfc/endpoint").toString();
			QString orderNo = settings.value("Sfc/order_no").toString();
			QString lineName = settings.value("Sfc/linename").toString();
			int cc = 0;
			for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
			{
				if (ui->tableWidget_2->item(i, 0)->checkState() == Qt::Unchecked)
					cc++;
			}
			//if(!sfcWin->GetPrintInfo(endpoint, orderNo, cc, lineName, msg) || !sfcWin->parsePrintInfo(msg, printInfo))
			//{
			//	sigStat.alarm = 0;
			//	int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"GetPrintInfoÊ§°Ü!\n%1").arg(msg), QString::fromUtf16(L"ÖØÊÔ"), QString::fromUtf16(L"ÔÝÍ£"));
			//	sigStat.alarm = 1;
			//	if(res == 1)
			//	{
			//		procFlag.printing_pause = true;
			//	}
			//	return;
			//}
			/*if (printInfo.child_serial.size() < cc)
			{
				sigStat.alarm = 0;
				int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"GetPrintInfoÒì³£!\n·µ»ØÐ¡°åºÅÂë¸öÊý²»Æ¥Åä, ÇëÇó%1¸ö, ·µ»Ø%2¸ö").arg(cc).arg(printInfo.child_serial.size()), QString::fromUtf16(L"ÖØÊÔ"), QString::fromUtf16(L"ÔÝÍ£"));
				sigStat.alarm = 1;
				if (res == 1)
				{
					procFlag.printing_pause = true;
				}
				return;
			}*/
			updateStatistics();
		}
#ifdef FoxlinkAdd
		if (!strEmployee.isNull())
		{
			if (ui->checkBox_5->isChecked())
			{
				int cc = 0;
				for (int i = 0; i < ui->tableWidget_2->rowCount(); i++)
				{
					if (ui->tableWidget_2->item(i, 0)->checkState() == Qt::Unchecked)
						cc++;
				}
				QString msg, strData;
				QString endpoint = settings.value("Sfc/endpoint").toString();
				QString lineName = settings.value("Sfc/linename").toString();
				int ws_mode = settings.value("Sfc/mode", 1).toInt();
				strData = QString("%1;25;%2;%3;%4;").arg(lineName).arg(strEmployee).arg(ui->lineEdit->text()).arg(cc);
				if (ws_mode == 0)
					sfcWin->SwSendData(strData, msg);
				else
					sfcWin->SaveTestData(endpoint, strData, msg);
				/*if (!sfcWin->parsePrintInfo(msg, printInfo))
				{
					on_pushButton_18_clicked();
					sigStat.alarm = 0;
					int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"»ñÈ¡×ÓÌõÂëÐÅÏ¢Ê§°Ü\n").arg(msg), QString::fromUtf16(L"ÔÝÍ£"), QString::fromUtf16(L"ÖÐÖ¹"));
					sigStat.alarm = 1;
					switch (res)
					{
					case 0:
						return;
					case 1:
						on_pushButton_5_clicked();
						break;
					}
					break;
				}*/
				updateStatistics();
			}
			//else
			{
				x = ui->tableWidget_3->item(0, 3)->text().toDouble();
				y = ui->tableWidget_3->item(0, 4)->text().toDouble();
				//z = settings.value("Position/mark1_z", 0).toDouble();
				smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
				//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
				//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
				procFlag.real_time = true;
				_step = 86;
				break;
			}
		}
		_step = 90;
		break;
	case 86:
		time.restart();
		_step = 87;
	case 87:
		if (time.elapsed() < delay_code) break;
		tcpSocket->readAll();
		tcpSocket->write("$B*b$E*");
		tcpSocket->waitForBytesWritten(3000);

		tcpSocket->waitForReadyRead(3000);
		readCode = tcpSocket->readAll().trimmed();

		if (readCode.isEmpty())
		{
			tcpSocket->write("$B*s$E*");
			tcpSocket->waitForBytesWritten(3000);

			tcpSocket->waitForReadyRead(3000);
			readCode = tcpSocket->readAll().trimmed();
		}
		//if(readCode.isEmpty()) 
		//	readCode = settings.value("Sfc/bound_serial").toString().toLatin1();
		////if(printInfo.panel_no.compare(readCode) != 0  && settings.value("Code/compare", true).toBool())
		if (readCode.isEmpty())
		{
			//if (ui->checkBox_5->isChecked())
			//{
			//	addMessage(QString::fromUtf16(L"ÖÎ¾ßÌõÂë½á¹û: \"%1\"").arg(readCode.constData()));
			//	printInfo.panel_no = readCode;
			//}
			//else
			{
				addMessage(QString::fromUtf16(L"ÖÎ¾ßÌõÂë½á¹û: \"%1\"").arg(readCode.constData()), Qt::red);
				on_pushButton_18_clicked();
				sigStat.alarm = 0;
				QString _station = settings.value("SFC/linename").toString();
				SaveTestData(_station + ";30;" + strEmployee + ";3;");
				int res = QMessageBox::information(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"ÌõÂë½á¹ûÒì³£"), QMessageBox::Retry, QMessageBox::Abort);
				SaveTestData(_station + ";30;" + strEmployee + ";23;");
				sigStat.alarm = 1;
				switch (res)
				{
				case QMessageBox::Retry:
					time.restart();
					procFlag.printing_pause = false;
					return;
				case QMessageBox::Abort:
					on_pushButton_5_clicked();
					break;
				}
			}
		}
		else
		{
			addMessage(QString::fromUtf16(L"ÖÎ¾ßÌõÂë½á¹û: \"%1\"").arg(readCode.constData()));
			printInfo.panel_no = readCode;

			if (!ui->checkBox_5->isChecked())
			{
				QString msg, strData;
				QString endpoint = settings.value("Sfc/endpoint").toString();
				QString lineName = settings.value("Sfc/linename").toString();
				int ws_mode = settings.value("Sfc/mode", 1).toInt();
				strData = lineName + ";9;" + readCode;

				if (ws_mode == 0)
					sfcWin->SwSendData(strData, msg);
				else
					sfcWin->SaveTestData(endpoint, strData, msg);
				/*if (!sfcWin->parsePrintInfo(msg, printInfo))
				{
					on_pushButton_18_clicked();
					sigStat.alarm = 0;
					int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"»ñÈ¡×ÓÌõÂëÐÅÏ¢Ê§°Ü\n").arg(msg), QString::fromUtf16(L"ÔÝÍ£"), QString::fromUtf16(L"ÖÐÖ¹"));
					sigStat.alarm = 1;
					switch (res)
					{
					case 0:
						return;
					case 1:
						on_pushButton_5_clicked();
						break;
					}
					break;
				}*/
				updateStatistics();
			}
		}
#endif
		_step = 90;
	case 90:
		if ((!ui->checkBox->isChecked() ||
			ui->tableWidget_2->item(_index, 0)->checkState() == Qt::Unchecked)
			&& ui->tableWidget->item(_index, 0)->checkState() == Qt::Checked)
		{
			_step = 91;
			break;
		}

		if (++_index < ui->tableWidget->rowCount())
			break;

		_step = 120;
		break;
	case 91:
		if (true)
		{
			// PCBÐý×ª½Ç¶È
			double u1 = 0;		// ½Ç¶È²¹³¥
			if (!markData[0].firstPos.isNull() && !markData[1].firstPos.isNull())
				u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			u1 += ui->tableWidget->item(_index, 5)->text().toDouble();
			double cx = settings.value("Offset/center_x", "0.000").toDouble();
			double cy = settings.value("Offset/center_y", "0.000").toDouble();
			double dx = settings.value("Offset/ofs_x", "0.000").toDouble();
			double dy = settings.value("Offset/ofs_y", "0.000").toDouble();
			double du = settings.value("Offset/ofs_u", "0.000").toDouble();
			QPointF p = QTransform().rotate(u1).map(QPointF(cx - dx, cy - dy));
			double ax = p.x() - (cx - dx);  	// ½Ç¶È²¹³¥
			double ay = p.y() - (cy - dy);  	// ½Ç¶È²¹³¥
			sumNumber = 1;
			if (ui->tableWidget->rowCount()-1  > _index)
			{
ADD:
				if (ui->tableWidget->item(_index + sumNumber, 0)->checkState() == Qt::Unchecked)
				{
					if (_index + sumNumber == ui->tableWidget->rowCount()-1)
					{
						goto IGNORE1;
					}
					sumNumber++;
					goto ADD;
				}
				//The same of X 
				if (ui->tableWidget->item(_index,1)->text().toDouble() == ui->tableWidget->item(_index+sumNumber, 1)->text().toDouble() && ui->tableWidget->item(_index, 5)->text().toInt() == ui->tableWidget->item(_index + sumNumber, 5)->text().toInt())
				{
					if (ui->tableWidget->item(_index,5)->text().toInt() == 90 || ui->tableWidget->item(_index, 5)->text().toInt() == 270)
					{
						if (flagSame != 2)
						{
							flyprintf.Pos[order] = (ui->tableWidget->item(_index, 4)->text().toDouble() - ay + dy) / pulseEquivalent[1];
							_index = _index + sumNumber;
							order++;
							flagSame = 1;
							_step = 90;
							break;
						}
					}
				}
				else
				{
					if (flagSame == 1)
					{
						flyprintf.Pos[order] = (ui->tableWidget->item(_index, 4)->text().toDouble() - ay + dy) / pulseEquivalent[1];
						order++;
					}
				}
				//the same of Y
				if(ui->tableWidget->item(_index, 2)->text().toDouble() == ui->tableWidget->item(_index + sumNumber, 2)->text().toDouble() && ui->tableWidget->item(_index, 5)->text().toInt() == ui->tableWidget->item(_index + sumNumber, 5)->text().toInt())
				{
					if (ui->tableWidget->item(_index, 5)->text().toInt() == 0 || ui->tableWidget->item(_index, 5)->text().toInt() == 180)
					{
						if (flagSame != 1)
						{
							flyprintf.Pos[order] = (ui->tableWidget->item(_index, 3)->text().toDouble() - ax + dx) / pulseEquivalent[0];
							_index = _index + sumNumber;
							order++;
							flagSame = 2;
							_step = 90;
							break;
						}
					}			
				}
				else 
				{
					if (flagSame == 2)
					{
						flyprintf.Pos[order] = (ui->tableWidget->item(_index, 3)->text().toDouble() - ax + dx) / pulseEquivalent[0];
						order++;
					}
				}
			}
			if (ui->tableWidget->rowCount() - 1 == _index)
			{
				if (flagSame == 1)
				{
					flyprintf.Pos[order] = (ui->tableWidget->item(_index, 4)->text().toDouble() - ay + dy) / pulseEquivalent[1];
					order++;
				}
				if (flagSame == 2)
				{
					flyprintf.Pos[order] = (ui->tableWidget->item(_index, 3)->text().toDouble() - ax + dx)/ pulseEquivalent[0];
					order++;
				}
			}
IGNORE1:
			z = settings.value("Print/z", 0).toDouble();
			u = settings.value("Print/u", 0).toDouble() + u1;
			while (u < -1) u += 360; while (u > 360) u -= 360;
			if (order == 0)
			{
				x = ui->tableWidget->item(_index, 3)->text().toDouble() - ax + dx;
				y = ui->tableWidget->item(_index, 4)->text().toDouble() - ay + dy;
				dx1 = offsetFly * cos(u*M_PI / 180);
				dy1 = offsetFly * sin(u*M_PI / 180);
				order = 1;
				if (ui->tableWidget->item(_index, 5)->text().toInt() == 0)
				{
					smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) - dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
					addMessage(QString("X  postion  %1").arg(x), Qt::blue);
					addMessage(QString("Y postion %1").arg(y), Qt::blue);
					flyprintf.Pos[0] = x / pulseEquivalent[0];
					flyprintf.axis = 0;
					flyprintf.mode = 1;
				}
				if (ui->tableWidget->item(_index, 5)->text().toInt() == 90)
				{
					smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos - dx1), (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
					addMessage(QString("X postion %1").arg(x), Qt::blue);
					addMessage(QString("Y postion %1").arg(y), Qt::blue);
					flyprintf.Pos[0] = y / pulseEquivalent[1];
					flyprintf.axis = 1;
					flyprintf.mode = 1;
				}
				if (ui->tableWidget->item(_index, 5)->text().toInt() == 180)
				{
					smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) -dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
					addMessage(QString("X postion %1").arg(x), Qt::blue);
					addMessage(QString("Y postion %1").arg(y), Qt::blue);
					flyprintf.Pos[0] = x / pulseEquivalent[0];
					flyprintf.axis = 0;
					flyprintf.mode = 2;
				}
				if (ui->tableWidget->item(_index, 5)->text().toInt() == 270)
				{
					smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos - dx1), (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
					addMessage(QString("X postion %1").arg(x), Qt::blue);
					addMessage(QString("Y postion %1").arg(y), Qt::blue);
					flyprintf.Pos[0] = y / pulseEquivalent[1];
					flyprintf.axis = 1;
					flyprintf.mode = 2;
				} 
			}
			else
			{
				x = ui->tableWidget->item(_index - order-sumNumber+2, 3)->text().toDouble() - ax + dx;
				y = ui->tableWidget->item(_index - order-sumNumber+2, 4)->text().toDouble() - ay + dy;
				dx1 = offsetFly * cos(u*M_PI / 180);
				dy1 = offsetFly * sin(u*M_PI / 180);
				if (flagSame == 1)
				{
					if (ui->tableWidget->item(_index, 5)->text().toInt() == 90)
					{
						smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) - dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
						addMessage(QString("X postion %1").arg(x), Qt::blue);
						addMessage(QString("Y postion %1").arg(y), Qt::blue);
						flyprintf.axis = 1;
						flyprintf.mode = 1;
					}	
					else
					{
						smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) - dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos) - dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
						addMessage(QString("X postion %1").arg(x), Qt::blue);
						addMessage(QString("Y postion %1").arg(y), Qt::blue);
						flyprintf.axis = 1;
						flyprintf.mode = 2;
					}
				}
				if (flagSame == 2)
				{
					if (ui->tableWidget->item(_index, 5)->text().toInt() == 0)
					{
						smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) - dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos)-dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
						addMessage(QString("X postion %1").arg(x), Qt::blue);
						addMessage(QString("Y postion %1").arg(y), Qt::blue);
						flyprintf.axis = 0;
						flyprintf.mode = 1;
					}
					else
					{
						smp86xHandler[0]->start(0, 1, (x / pulseEquivalent[0] - ss[0].axis_status[0].logicPos) -dx1, (y / pulseEquivalent[1] - ss[0].axis_status[1].logicPos)-dy1, speedValue[0], speedValue[1] * speed, speedValue[2] / 1000.0);
						addMessage(QString("X postion %1").arg(x), Qt::blue);
						addMessage(QString("Y postion %1").arg(y), Qt::blue);

						flyprintf.axis = 0;
						flyprintf.mode = 2;
					}
				}
			}
			
			smp86xHandler[0]->start(2, (u / pulseEquivalent[3] - ss[0].axis_status[2].logicPos), speedValue[9], speedValue[10] * speed, speedValue[11] / 1000.0);
			flyprintf.order = order;
			if (smp86xHandler[0]->writeRawData(0x180, sizeof(flyprintf)/2, (ushort *)&flyprintf) == -1)
				QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"Êý¾Ý´«ÊäÊ§°Ü"));
			QString showout;
			for(int a = 0; a<order;a++)
				addMessage(showout.setNum(flyprintf.Pos[a]), Qt::blue);
			procFlag.real_time = true;
			if (order != 1)
			{
				_step = 102;
				break;
			}
			_step = 92;
		}
		break;
	case 92:
	{	
// 	_NEXT:
// 		QString textModel = ui->tableWidget->item(_index, 6)->text();
// 		curPrintf = ui->tableWidget->item(_index, 6)->text().toInt()-1;	
// 		chushi = 1;
// 		updateStatistics();
// 		text = ui->lineEdit_2->text();
// 		_Database::check(text.toLatin1(), t);
// 		if (t != 0)
// 		{
// 			sigStat.alarm = 0;
// 			if (!ui->checkBox_7->isChecked())
// 			{
// 				goto FLAG2;
// 				sigStat.alarm = 1;
// 			}
// 			int res = QMessageBox::warning(this, QString::fromUtf16(L"·¢ÏÖÖØÂë"), QString::fromUtf16(L"%1\nµÄÉÏ´Î´òÓ¡Ê±¼äÎª:\n%2").arg(text).arg(ctime(&t)), QString::fromUtf16(L"ÏÂÒ»¸ö"), QString::fromUtf16(L"ÔÝÍ£"));
// 			sigStat.alarm = 1;
// 			switch (res)
// 			{
// 			case 0:
// 				updateStatistics();
// 				goto _NEXT;
// 				break;
// 			case 1:
// 				procFlag.printing_pause = true;
// 				return;
// 			}
// 		}	
// FLAG2:
// 		if (!ui->checkBox_9->isChecked())
// 		{
// 			QString Schangtext = QString("P1%1").arg(textModel);
// 			bool exit3 = sendInkData(device, Schangtext.toLatin1());
// 			if (!exit3)
// 			{
// 				QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨¸ü¸ÄÎÄ±¾\n"), QString::fromUtf16(L"È·¶¨"));
// 				procFlag.printing_pause = true;
// 				return;
// 			}
// 			bool exit2 = printfCurText();    //Æô¶¯ÅçÓ¡
// 			if (!exit2)
// 			{
// 				return;
// 			}
// 			ui->tableWidget->item(_index, 0)->setText(text);
// 		}	
		_step = 100;
		break;
	}
	case 100:
	{
		_step = 101;
		time.restart();
		break;
	}
	case 101:
		if(time.elapsed() < delay_print)
			break;
		{
			double u1 = 0;
			if (!markData[0].firstPos.isNull() && !markData[1].firstPos.isNull())
				u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			u1 += ui->tableWidget->item(_index, 5)->text().toDouble();
			double division = settings.value("Print/division", 40).toDouble();
			dist = settings.value("Print/dist", 10000).toInt() + offsetFly;
			angle = settings.value("Print/angle", 0).toDouble() + u1;
			dist1 = dist*cos(angle*M_PI / 180);
			dist2 = dist*sin(angle*M_PI / 180);
			smp86xHandler[0]->start(0, 1, 3, dist1, dist2, dist / division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
			//Sleep(100);
			procFlag.real_time = true;
			_step = 110;
			flagSame = 0;
			addMessage(QString("single%1").arg(_index), Qt::blue);
			order = 0;
			break;
		}
	case 102:
		_step = 103;
		break;
	case 103:
		_step = 104;
		time.restart();
		break;
	case 104:
		if (time.elapsed() < delay_print)
			break;
		{
			// PCBÐý×ª½Ç¶È
			double u1 = 0;		// ½Ç¶È²¹³¥
			int dist3 = 0;
			if (!markData[0].firstPos.isNull() && !markData[1].firstPos.isNull())
				u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			u1 += ui->tableWidget->item(_index, 5)->text().toDouble();
			double division = settings.value("Print/division", 40).toDouble();
			dist = settings.value("Print/dist", 10000).toInt() + offsetFly;
			angle = settings.value("Print/angle", 0).toDouble() + u1;		
			if (flagSame == 1)
			{
				double y1 = ui->tableWidget->item(_index - order - sumNumber + 2, 4)->text().toDouble();
				double y2 = ui->tableWidget->item(_index, 4)->text().toDouble();
				dist3 = abs(y2 - y1)/ pulseEquivalent[1] + dist;
			}
			if (flagSame == 2)
			{
				double x1 = ui->tableWidget->item(_index - order - sumNumber + 2, 3)->text().toDouble();
				double x2 = ui->tableWidget->item(_index, 3)->text().toDouble();
				dist3 = abs(x2 - x1)/ pulseEquivalent[0] + dist; 
			}
			dist1 = dist3*cos(angle*M_PI / 180);
			dist2 = dist3*sin(angle*M_PI / 180);
			smp86xHandler[0]->start(0, 1, 3, dist1, dist2, dist3/ division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
			procFlag.real_time = true;
			order = 0;
			flagSame = 0;
			_step = 110;
			addMessage(QString("more%1").arg(_index), Qt::blue);
		}
		break;
	case 110:
	{
		//updateStatistics();
		if (++_index < ui->tableWidget->rowCount())
		{
			_step = 90;
			break;
		}
		_step = 120;
		addMessage(QString("printf completed!"), Qt::blue);
		break;
	}
	case 115:
		smp86xHandler[0]->setOutput(0, ui->checkBox_2->isChecked() ? 0 : 1);
		smp86xHandler[0]->setOutput(1, ui->checkBox_3->isChecked() ? 0 : 1);
		

		smp86xHandler[0]->setOutput(2, 0);
		_step = 116;
		time.restart();
		break;
	case 116:
		if(time.elapsed() < qMax(750, delay_print))
			break;
		{
			double u1 = 0;
			if(!markData[0].firstPos.isNull() && !markData[1].firstPos.isNull())
				u1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).angleTo(QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()));
			//u1 += ui->tableWidget->item(_index, 5)->text().toDouble();
			double division = settings.value("Print/division", 40).toDouble();
			dist = settings.value("Print/dist", 10000).toInt();
			angle = settings.value("Print/angle", 0).toDouble()+u1;
			dist1 = dist*cos(angle*M_PI/180);
			dist2 = dist*sin(angle*M_PI/180);
			//smp86xHandler[0]->start(0, 1, dist1, dist2, speedValue[12], speedValue[13], speedValue[14]/1000.0);
			smp86xHandler[0]->start(0, 1, 3, dist1, dist2, dist/division, speedValue[12], speedValue[13], speedValue[14]/1000.0);
			procFlag.real_time = true;
			_step = 117;
		}
		break;
	case 117:
		smp86xHandler[0]->setOutput(2, 1);
		_step = 130;
		break;
	case 120:
		//µÚËÄÖá»ØÔ­µã
		smp86xHandler[0]->home(3);
		addMessage(QString("Axis 4 home!"), Qt::blue);
		_step = 121;
		break;
	case 121:
		/*smp86xHandler[0]->start(2, (0 / pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8] / 1000.0);*/
		procFlag.real_time = true;
		_step = 130;
		break;
	case 130:
		procFlag.scancode_start = ui->checkBox_4->isChecked();
		addMessage(QString("judge scancode"), Qt::blue);
		_step = 140;
		break;
	case 140:
		if(procFlag.scancode_start)
			break;
//
//#ifdef BarcodePrintService
//		if (ui->actionSfc->isChecked() && printInfo.child_serial.size())
//		{
//			QString msg;
//			QString endpoint = settings.value("Sfc/endpoint").toString();
//			QString orderNo  = settings.value("Sfc/order_no").toString();
//			QString stationName  = settings.value("Sfc/station_name").toString();
//			if (!sfcWin->FinishPrintInfo(endpoint, orderNo, stationName, printInfo.child_serial.join(";"), printInfo.bound_serial, msg))
//			{
//				sigStat.alarm = 0;
//				int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"FinishPrintInfoÊ§°Ü!\n%1").arg(msg), QString::fromUtf16(L"ºöÂÔ"), QString::fromUtf16(L"ÔÝÍ£"));
//				sigStat.alarm = 1;
//				if(res == 1)
//				{
//					procFlag.printing_pause = true;
//					return;
//				}
//			}
//		}
//#endif // BarcodePrintService
//#ifdef FoxlinkAdd
//		if (!strEmployee.isNull() && ui->actionSfc->isChecked())
//		{
//			QString lineName = settings.value("Sfc/linename").toString();
//			QString strData;
//			if(!ui->checkBox_5->isChecked())
//			{
//				if (printInfo.bound_serial == "OK")
//					strData = lineName + ";7;" + strEmployee + ";" + printInfo.panel_no + ";OK;";
//				else
//				{
//					strData = lineName + ";51;" + strEmployee + ";" + printInfo.panel_no + ";NG;";
//					printInfo.child_state.removeAll("OK");
//					strData += printInfo.child_state.join("|") + ";";
//					//for (int _i = 0; _i < printInfo.child_state.size(); _i++)
//					//	if (printInfo.child_state[_i] != "OK")
//					//		strData += QString("%1:EC01|").arg(_i + 1);
//					//strData.replace(QRegExp("\\|$"), ";");
//				}
//				if (!SaveTestData(strData))
//				{
//					//sigStat.alarm = 0;
//					//int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), msg, QString::fromUtf16(L"ÖÐÖ¹"));
//					//sigStat.alarm = 1;
//					on_pushButton_5_clicked();
//				}
//			}
//			else
//			{
//				if (printInfo.bound_serial != "OK")
//				{
//					strData = lineName + ";51;" + strEmployee + ";" + printInfo.panel_no + ";NG;";
//					printInfo.child_state.removeAll("OK");
//					strData += printInfo.child_state.join("|") + ";";
//					//for (int _i = 0; _i < printInfo.child_state.size(); _i++)
//					//	if (printInfo.child_state[_i] != "OK")
//					//		strData += QString("%1:EC01|").arg(_i + 1);
//					//strData.replace(QRegExp("\\|$"), ";");
//					SaveTestData(strData);
//
//					sigStat.alarm = 0;
//					SaveTestData(lineName + ";30;" + strEmployee + ";3;");
//					int res = QMessageBox::warning(this, QString::fromUtf16(L"´íÎó"), QString::fromUtf16(L"ÅçÂë½á¹û¼ì²éNG"), QString::fromUtf16(L"ÖªµÀÁË"), QString::fromUtf16(L"Í£Ö¹"));
//					SaveTestData(lineName + ";30;" + strEmployee + ";23;");
//					sigStat.alarm = 1;
//					if (res == 1)
//					{
//						procFlag.printing_start = false;
//						procFlag.scancode_start = false;
//						return;
//					}
//				}
//				else
//				{
//					strData = lineName + ";26;" + strEmployee + ";" + ui->lineEdit->text() + ";" + printInfo.panel_no + ";" + printInfo.child_serial.join("|") + ";";
//					if (!SaveTestData(strData))
//					{
//						//sigStat.alarm = 0;
//						//int res = QMessageBox::warning(this, QString::fromUtf16(L"SFC´íÎó"), msg, QString::fromUtf16(L"ÖÐÖ¹"));
//						//sigStat.alarm = 1;
//						on_pushButton_5_clicked();
//					}
//				}
//			}
//		}
//#endif // FoxlinkAdd
//
//		if(settings.value("debug/pause_when_finished", false).toBool())
//			on_pushButton_18_clicked();
		addMessage(QString("no scancode"), Qt::blue);
		_step = 150;
		break;
	case 150:
		procFlag.conveyor_ready = false;
		_step = 0;
		break;
	}
}
#endif // 0

void PrintMark::checkError(SMP86X_STATUS ss[])
{
	QSettings settings;
	static QIcon errIcon(":/Resources/signal-stop.png");
	static QIcon altIcon(":/Resources/signal-attention.png");
	static SMP86X_STATUS _ss[2] = {ss[0], ss[1]};
	int rowCount = ui->listWidget_2->count();
	ui->listWidget_2->setUpdatesEnabled(false);
	int currentRow = ui->listWidget_2->currentRow();
	ui->listWidget_2->clear();
	sigStat.red = 1;
	sigStat.yellow = 1;
	if (((ss[0].inputs>>9) & 0x1) == 1 )	// ¼±Í£°´ÏÂ
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(errIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"¼±Í£±»°´ÏÂ"));
		sigStat.red = 0;

		if (((_ss[0].inputs>>9) & 0x1) == 0)
		{
			smp86xHandler[0]->stopAll();
			smp86xHandler[1]->stopAll();
			sigStat.alarm = 0;
		}
	}

	if (((ss[0].axis_status[0].state >> 15) & 0x1) == 1
 		|| ((ss[0].axis_status[1].state >> 15) & 0x1) == 1
 		|| ((ss[0].axis_status[2].state >> 15) & 0x1) == 1
		)	// ËÅ·þ±¨¾¯
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(errIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"ËÅ·þ±¨¾¯"));
		sigStat.red = 0;
		if (((_ss[0].axis_status[0].state >> 15) & 0x1) == 0
			&& ((_ss[0].axis_status[1].state >> 15) & 0x1) == 0
			&& ((_ss[0].axis_status[2].state >> 15) & 0x1) == 0)	// ËÅ·þ±¨¾¯
			sigStat.alarm = 0;
	}

#ifdef _OLD_VERSION
 	if (((ss[1].inputs>>6) & 0x1) == 1)  // ÆøÑ¹
 	{
 		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
 		__qlistwidgetitem->setIcon(altIcon);
 		__qlistwidgetitem->setText(QString::fromUtf16(L"ÆøÑ¹²»×ã"));
 		sigStat.yellow = 0;
 		if(((_ss[1].inputs>>1) & 0x1) == 0)
 			sigStat.alarm = 0;
 	}
#else
	//if (((ss[1].inputs>>18) & 0x1) == 1)	// ÆøÑ¹
	//{
	//	QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
	//	__qlistwidgetitem->setIcon(altIcon);
	//	__qlistwidgetitem->setText(QString::fromUtf16(L"ÆøÑ¹²»×ã"));
	//	sigStat.yellow = 0;
	//	if(((_ss[1].inputs>>18) & 0x1) == 0)
	//		sigStat.alarm = 0;
	//}
#endif // _OLD_VERSION

#ifdef _OLD_VERSION
	if (((ss[0].inputs>>2) & 0x1) == 0)	// 
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(altIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"Ö±Í¨Ä£Ê½"));
		//sigStat.yellow = 0;
		//if(((_ss[0].inputs>>2) & 0x1) == 1)
		//	sigStat.alarm = 0;
	}

	if (labelCom[0]->text() == "NULL")	//°å¿¨AÃ»Á¬½Ó
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(errIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"°å¿¨AÃ»Á¬½Ó"));
		sigStat.red = 0;

	}

 	if (labelCom[1]->text() == "NULL")	// °å¿¨BÃ»Á¬½Ó
 	{
 		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
 		__qlistwidgetitem->setIcon(errIcon);
 		__qlistwidgetitem->setText(QString::fromUtf16(L"°å¿¨BÃ»Á¬½Ó"));
 		sigStat.red = 0;

 	}

	if (((ss[0].inputs>>7) & 0x1) == 1)	// Ç°ÃÅ
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(altIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"Ç°ÃÅÎ´¹ØÉÏ"));
		sigStat.yellow = 0;
	}

	if (((ss[0].inputs>>8) & 0x1) == 1)	// ºóÃÅ
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(altIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"ºóÃÅÎ´¹ØÉÏ"));
		sigStat.yellow = 0;
	}
#endif // _OLD_VERSION

	if (((ss[0].inputs>>4) & 0x1) == 0 && procFlag.printing_start)	// ÔÝÍ£
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(altIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"ÒÑÔÝÍ£"));
		sigStat.yellow = 0;
	}

	if(settings.value("Code/enable", true).toBool() || ui->actionSfc->isChecked())
	{
		if (ui->lcdNumber_3->intValue() <= 0)
		{
			QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
			__qlistwidgetitem->setIcon(errIcon);
			__qlistwidgetitem->setText(QString::fromUtf16(L"¶þÎ¬ÂëÐòÁÐÒÑÓÃÍê"));
			sigStat.red = 0;
		}
		else if (ui->lcdNumber_3->intValue() < 300)
		{
			QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
			__qlistwidgetitem->setIcon(altIcon);
			__qlistwidgetitem->setText(QString::fromUtf16(L"¶þÎ¬ÂëÐòÁÐ¼´½«ÓÃÍê"));
			sigStat.yellow = 0;
		}
	}

	int run_time = settings.value("Maintain/run").toInt();
	int duration = settings.value("Maintain/duration", 360).toInt();
	if (run_time/3600 > duration)
	{
		QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui->listWidget_2);
		__qlistwidgetitem->setIcon(altIcon);
		__qlistwidgetitem->setText(QString::fromUtf16(L"Çë±£Ñø»úÌ¨"));
		sigStat.yellow = 0;
	}

// 	if(ui->pushButton_4->isEnabled() && ((ss[0].inputs>>4)&0x1) == 0 && ((_ss[0].inputs>>4)&0x1) == 1)		// ¿ªÊ¼
// 		on_pushButton_4_clicked();
// 
// 	if(((ss[0].inputs>>6)&0x1) == 0 && ((_ss[0].inputs>>6)&0x1) == 1)		// ÔÝÍ£
// 		on_pushButton_18_clicked();
// 
// 	if(((ss[0].inputs>>6)&0x1) == 1 && ((_ss[0].inputs>>6)&0x1) == 0)		// ÔÝÍ£
// 	{
// 		procFlag.printing_pause = false;
// 	}
// 
// 	if (((ss[0].inputs >> 5) & 0x1) == 0 && ((_ss[0].inputs >> 5) & 0x1) == 1)		// Çå±¨¾¯
// 	{
// 		on_pushButton_15_clicked();
// 		procFlag.conveyor_start = false;
// 		procFlag.conveyor_ready = false;
// 		smp86xHandler[1]->stopAll();
// 		smp86xHandler[1]->setOutput(0, 1);
// 		smp86xHandler[1]->setOutput(1, 1);
// 		smp86xHandler[1]->setOutput(8, 1);
// 		smp86xHandler[1]->setOutput(9, 1);     //ÖØÖÃ	(ÕâÊÇ¸öÖØÖÃ°´Å¥ÁË£¬µ«²»ÖªµÀÎªÊ²Ã´ÎÒ»¹ÊÇ¶à¼ÓÁË±¨¾¯)
// 	}

	ui->listWidget_2->setCurrentRow(currentRow);
	ui->listWidget_2->setUpdatesEnabled(true);

	memcpy(_ss, ss, sizeof(SMP86X_STATUS)*2);
}

void PrintMark::slotReset()
{
	smp86xHandler[0]->stopAll();
	smp86xHandler[1]->stopAll();
	for (int i=0; i<16; i++)
	{
		smp86xHandler[0]->setOutput(i, 1);
		smp86xHandler[1]->setOutput(i, 1);
	}

	memset(&procFlag, 0, sizeof(PROCFLAG));
	procFlag.homing = true;
}

void PrintMark::on_horizontalSlider_valueChanged( int value )
{
	if(ui->toolButton->isChecked())
		smp86xHandler[0]->setPWM(0, value);
	ui->label_6->setNum(100-value*100/255);
}

bool PrintMark::visionPos(float& x, float& y, float& u, int m)
{
	QSettings settings;
	double ix = 0.0, iy = 0.0, ia = 0.0;
	QTcpSocket socket;
	socket.connectToHost(QHostAddress(QHostAddress::LocalHost), 5800);
	if (!socket.waitForConnected(5000))
		return false;

	sendTcpData(&socket, m);
	if (!readTcpData(&socket, &ix, &iy, &ia))
		return false;

	QTransform trans[4];
	//QList<QVariant> data1 = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());
	trans[0] = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());
	int resx[4], resy[4];
	resx[0] = settings.value("Calibration/res_w1", 0).toInt();
	resy[0] = settings.value("Calibration/res_h1", 0).toInt();
	ix = ix - resx[0]/2.0;	iy = iy - resy[0]/2.0;

	QPointF p; 
	affine_trans_xyu(trans[0], QPointF(iy, ix), ia*M_PI/180.0, p, u);
	u = u*180.0/M_PI;

	p = trans[0].map(QPointF()) - p;
	x = p.y(); y = p.x();
	return true;
}

bool PrintMark::visionValid()
{
	double ix = 0.0, iy = 0.0, ia = 0.0;
	QTcpSocket socket;
	socket.connectToHost(QHostAddress(QHostAddress::LocalHost), 5800);
	if (!socket.waitForConnected(5000))
		return false;

	sendTcpData(&socket, 1);
	if (!readTcpData(&socket, &ix, &iy, &ia))
		return false;
	return true;
}

bool PrintMark::printfCurText()
{
	QSettings settings;
	QString ink_data = NULL;
	QString ink_data2 = NULL;
	inknum[curPrintf] = settings.value(QString("ink_printf%1/text_number").arg(curPrintf), 0).toInt();
	if (inknum[curPrintf] == 0)
	{
		QMessageBox::about(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"Ã»ÓÐÉèÖÃÅçÓ¡ÐÅÏ¢·¢ËÍ"));
		procFlag.printing_start = false;
		procFlag.scancode_start = false;
		return false;
	}
	for (int j = 0; j < inknum[curPrintf]; j++)
	{
		QString TC = settings.value(QString("ink_printf%1/text%2").arg(curPrintf).arg(j), NULL).toString();
		TC.remove(0, 2);
		ink_data = ink_data.append(TC);
	}
INK_SEND:
	//QString send_inkdata, send_inkdata2,sendCount;
	////¼ÆËã·¢ËÍÊý¾Ý³¤¶È
	//int countData = ink_data.size();
	//if (countData<10)
	//	sendCount = "000" + QString::number(countData);
	//else if (countData<100)
	//	sendCount = "00" + QString::number(countData);
	//else if (countData<1000)
	//	sendCount = "0" + QString::number(countData);
	//else
	//	sendCount = QString::number(countData);
	//send_inkdata = QString("OE%1").arg(sendCount) + ink_data + QString("");
	//addMessage(QString("send data is %1/n").arg(send_inkdata), Qt::blue);
	//inkbool = sendInkData(device, send_inkdata.toLatin1());
	QString send_inkdata, send_inkdata2;
	send_inkdata = QString("") + ink_data + QString("");
	addMessage(QString("send data is %1/n").arg(send_inkdata), Qt::blue);
	inkbool = sendInkData(ink_device, send_inkdata.toLatin1());
	if (!inkbool)
	{
		Sleep(100);
		inkbool = sendInkData(device, send_inkdata.toLatin1());
	}
	if (!inkbool)
	{
		int res = QMessageBox::warning(this, QString::fromUtf16(L"´íÎó"), QString::fromUtf16(L"ÃüÁî·¢ËÍ´íÎó!Çë¼ì²éÍ¨Ñ¶£¡"), QString::fromUtf16(L"ÖØÐÂ·¢ËÍ"), QString::fromUtf16(L"Í£Ö¹"));
		if (res == 0)
			goto INK_SEND;
		if (res == 1)
		{
			procFlag.printing_start = false;
			procFlag.scancode_start = false;
			return false;
		}
	}
	return true;
}

void PrintMark::printfmove()
{
	QSettings settings;
	int dist = settings.value("Print/dist", 10000).toInt();
	double angle = settings.value("Print/angle", 0).toDouble();
	double printz = settings.value("Print/z", 0).toDouble();
	double printu = settings.value("Print/u", 0).toDouble();
	int dist1 = dist*cos(angle*M_PI / 180);
	int dist2 = dist*sin(angle*M_PI / 180);
	int delay = settings.value("Print/delay", 100).toInt();
	double division = settings.value("Print/division", 40).toDouble();
	if (angle == 0)
		smp86xHandler[0]->start(0, 1, 3, dist1 + offsetFly, dist2, (dist + offsetFly) / division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
	if(angle == 90)
		smp86xHandler[0]->start(0, 1, 3, dist1, dist2 + offsetFly, (dist + offsetFly) / division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
	if(angle == 180)
		smp86xHandler[0]->start(0, 1, 3, dist1 - offsetFly, dist2, (dist + offsetFly) / division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
	if(angle == -90)
		smp86xHandler[0]->start(0, 1, 3, dist1, dist2 - offsetFly, (dist + offsetFly) / division, speedValue[12], speedValue[13], speedValue[14] / 1000.0);
}


void PrintMark::addMessage( const QString& msg, QColor color)
{
	if (ui->listWidget->count() > 499)
		delete ui->listWidget->takeItem(0);

	QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
	item->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")+": "+msg);
	item->setTextColor(color);
	ui->listWidget->scrollToItem(item);
}

void PrintMark::runCpk( SMP86X_STATUS ss[] )
{
	static int _step = 0, _index = 0;
	static QTime time;
	if(!procFlag.cpk_start)
	{
		_step = 0;
		_index = 0;
		return;
	}

	if(isRunning(ss[0]))
		return;

	QSettings settings;
	float x, y, z, u;

	switch(_step)
	{
	case 0:
		x = ui->tableWidget_2->item(_index, 1)->text().toDouble();
		y = ui->tableWidget_2->item(_index, 2)->text().toDouble();
		z = settings.value("Position/mark1_z", 0).toDouble();//settings.value("Print/z", 0).toDouble();
		//smp86xHandler[0]->start(0, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
		//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
		//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
		smp86xHandler[0]->setPWM(0, ui->horizontalSlider->value());
		procFlag.real_time = true;
		_step = 30;
		break;
	case 10:
		time.restart();
		_step = 20;
		break;
	case 20:
		if(time.elapsed() < settings.value("Delay/snap", 50).toInt())
			break;
		if(!_visionPos(x, y, u, 0))
			x = y = u = 0.0;

		{
			QFile file("cpkdata.txt");
			if(file.open(QFile::WriteOnly|QFile::Append))
			{
				QTextStream out(&file);
				out << qSetFieldWidth(10) << x << y << ss[0].axis_status[0].logicPos*pulseEquivalent[0] << ss[0].axis_status[1].logicPos*pulseEquivalent[1] << "\r\n";
				file.close();
			}
		}
		_step = 30;
		break;
	case 30:
		if(++_index >= ui->tableWidget_2->rowCount())
			_index = 0;

		_step = 0;
		break;
	}
}

void PrintMark::on_actionRunCpk_triggered()
{
	if(ui->tableWidget_2->rowCount() > 0)
		procFlag.cpk_start = true;
	else
		QMessageBox::information(this, QString::fromUtf16(L"´íÎó"), QString::fromUtf16(L"Êý¾ÝÎ´ÉèÖÃ!"));
}

void PrintMark::on_toolButton_clicked( bool checked )
{
	smp86xHandler[0]->setPWM(0, checked ? ui->horizontalSlider->value() : 0);
}

void PrintMark::on_toolButton_2_clicked()
{
	QMenu menu;
	menu.addActions(QList<QAction*>() << ui->actionTest << ui->actionSetup << ui->actionReset);
	QAction* action = menu.exec(QCursor::pos());
	if (action == ui->actionTest)
	{
		float x, y, u;
		if(_visionPos(x, y, u, 0))
		{
			SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
			markData[0].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[0].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			double markDist1 = QLineF(markData[0].firstPos.toPointF(), markData[1].firstPos.toPointF()).length();
			double markDist2 = QLineF(markData[0].curntPos.toPointF(), markData[1].curntPos.toPointF()).length();
			addMessage(QString::fromUtf16(L"»ù×¼1: %1\t%2\t%3").arg(markData[0].curntPos.x(), 0, 'f', 3).arg(markData[0].curntPos.y(), 0, 'f', 3).arg(u, 0, 'f', 3));
			addMessage(QString::fromUtf16(L"¾àÀë: %1/%2").arg(abs(markDist2 - markDist1), 0, 'f', 3).arg(QSettings().value("mark_dist_diff", 3).toDouble(), 0, 'f', 3));
		}
		else
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼1Ê§°Ü"), Qt::red);
		}
	}
	if (action == ui->actionSetup)
	{
		QSettings settings;
		float x, y, u;
		if(_visionPos(x, y, u, 0))
		{
			SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
			markData[0].firstPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[0].firstPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			markData[0].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[0].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
			settings.setValue("Position/mark1_x", markData[0].firstPos.x());
			settings.setValue("Position/mark1_y", markData[0].firstPos.y());
			addMessage(QString::fromUtf16(L"ÉèÖÃ»ù×¼1³É¹¦"));
			setWindowModified(true);
			RunParams* runParams = findChild<RunParams*>();
			if (runParams) runParams->close();
		}
	}
	if (action == ui->actionReset)
	{
		markData[0].firstPos = markData[0].curntPos = QVector3D();
		ui->label_4->setText("0.000 0.000 0");
		setWindowModified(true);
	}
}

void PrintMark::on_toolButton_3_clicked()
{
	QMenu menu;
	menu.addActions(QList<QAction*>() << ui->actionTest << ui->actionSetup << ui->actionReset);
	QAction* action = menu.exec(QCursor::pos());
	if (action == ui->actionTest)
	{
		float x, y, u;
		if(_visionPos(x, y, u, 0))
		{
			SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
			markData[1].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[1].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			double markDist1 = QLineF(markData[1].firstPos.toPointF(), markData[1].firstPos.toPointF()).length();
			double markDist2 = QLineF(markData[1].curntPos.toPointF(), markData[1].curntPos.toPointF()).length();
			addMessage(QString::fromUtf16(L"»ù×¼2: %1\t%2\t%3").arg(markData[1].curntPos.x(), 0, 'f', 3).arg(markData[1].curntPos.y(), 0, 'f', 3).arg(u, 0, 'f', 3));
			addMessage(QString::fromUtf16(L"¾àÀë: %1/%2").arg(abs(markDist2 - markDist1), 0, 'f', 3).arg(QSettings().value("mark_dist_diff", 3).toDouble(), 0, 'f', 3));
		}
		else
		{
			addMessage(QString::fromUtf16(L"»ñÈ¡»ù×¼2Ê§°Ü"), Qt::red);
		}
	}
	if (action == ui->actionSetup)
	{
		QSettings settings;
		float x, y, u;
		if(_visionPos(x, y, u, 0))
		{
			SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
			markData[1].firstPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[1].firstPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			markData[1].curntPos.setX(x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
			markData[1].curntPos.setY(y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
			ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
			settings.setValue("Position/mark2_x", markData[1].firstPos.x());
			settings.setValue("Position/mark2_y", markData[1].firstPos.y());
			addMessage(QString::fromUtf16(L"ÉèÖÃ»ù×¼2³É¹¦"));
			setWindowModified(true);
			RunParams* runParams = findChild<RunParams*>();
			if (runParams) runParams->close();
		}
	}
	if (action == ui->actionReset)
	{
		markData[1].firstPos = markData[1].curntPos = QVector3D();
		ui->label_5->setText("0.000 0.000 0");
		setWindowModified(true);
	}
}

void PrintMark::on_pushButton_22_clicked()
{
	timeRecord->show();
	timeRecord->raise();
	QSize size = (frameSize() - timeRecord->frameSize()) / 2;
	QPoint topLeft = frameGeometry().topLeft();
	timeRecord->move(size.width()+topLeft.x(), size.height()+topLeft.y());
	timeRecord->setWindowState((timeRecord->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PrintMark::on_pushButton_23_clicked()
{
	if (labelCom[2]->text() != "NULL")
	{
		QByteArray device_data = QString("OE00002").toLatin1();
    	QByteArray device_data2 = QString("OE00001").toLatin1();
		sendpre = sendInkData(device, device_data);
		sendpre2 = sendInkData(device, device_data2);
		if (!sendpre && !sendpre2)
			QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨½øÐÐ³õÊ¼»¯\n"), QString::fromUtf16(L"È·¶¨"));
		else
			addMessage(QString::fromUtf16(L"³õÊ¼»¯³É¹¦"),Qt::blue);
	}
}

void PrintMark::on_pushButton_24_clicked()
{
 	if (labelCom[2]->text() != "NULL")
 	{
 		QString Schangtext = QString("P100%1").arg(ui->comboBox_2->currentIndex() + 1);
 		bool exit3 = sendInkData(device, Schangtext.toLatin1());
 		if (!exit3)
 			QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÎÞ·¨¸ü¸ÄÎÄ±¾\n"), QString::fromUtf16(L"È·¶¨"));
 		else
 		{
 			addMessage(QString::fromUtf16(L"ÎÄ±¾¼¤»î³É¹¦"), Qt::blue);
			curPrintf = ui->comboBox_2->currentIndex();
			addMessage(QString("%1").arg(curPrintf), Qt::blue);
		}
	}
	else
	{
		QMessageBox::information(this, QString::fromUtf16(L"ÅçÂë»ú´íÎó"), QString::fromUtf16(L"ÅçÂë»úÃ»ÓÐÁ¬½Ó\n"), QString::fromUtf16(L"È·¶¨"));
	}
}

void PrintMark::on_pushButton_25_clicked()
{
	QSettings settings;
	int valueAxisX = settings.value("Conveyor/XsetWide", 0).toInt();
	int currentX = smp86xHandler[1]->getSmp86xStatus().axis_status[0].logicPos;
	int speedX[3];
	for (size_t i = 0; i < 3; i++)
	{
		speedX[i] = settings.value(QString("Conveyor/speed_%1").arg(i+6), 1000).toInt();
	}
	smp86xHandler[1]->start(0, valueAxisX - currentX, speedX[0], speedX[1], speedX[2]/1000.0);
}

void PrintMark::on_pushButton_26_clicked()
{
	for (int i = 0; i < ui->tableWidget->rowCount(); i++)
	{
		if (ui->tableWidget->item(i,5)->text().toInt() == 0)
		{
			ui->tableWidget->item(i, 0)->setBackground(Qt::white);
		}
		if (ui->tableWidget->item(i, 5)->text().toInt() == 90)
		{
			ui->tableWidget->item(i, 0)->setBackground(Qt::lightGray);
		}
		if (ui->tableWidget->item(i, 5)->text().toInt() == 180)
		{
			ui->tableWidget->item(i, 0)->setBackground(Qt::gray);
		}
		if (ui->tableWidget->item(i, 5)->text().toInt() == 270)
		{
			ui->tableWidget->item(i, 0)->setBackground(Qt::darkGray);
		}
	}
}

void PrintMark::drawToAngel()
{
	for (int j = 0; j < ui->tableWidget->rowCount(); j++)
	{
		if (ui->tableWidget->item(j, 5)->text().toInt() == 0)
		{
			for (int i = 0; i < ui->tableWidget->columnCount(); i++)
			{
				ui->tableWidget->item(j, i)->setBackground(QColor("#FFFFFF"));
			}
		}
		if (ui->tableWidget->item(j, 5)->text().toInt() == 90)
		{
			for (int i = 0; i < ui->tableWidget->columnCount() ; i++)
			{
				ui->tableWidget->item(j, i)->setBackground(QColor("#FDECA6"));
			}
		}
		if (ui->tableWidget->item(j, 5)->text().toInt() == 180)
		{
			for (int i = 0; i < ui->tableWidget->columnCount(); i++)
			{
				ui->tableWidget->item(j, i)->setBackground(QColor("#FFFB3B"));
			}
		}
		if (ui->tableWidget->item(j, 5)->text().toInt() == 270)
		{
			for (int i = 0; i < ui->tableWidget->columnCount(); i++)
			{
				ui->tableWidget->item(j, i)->setBackground(QColor("#AED581"));
			}
		}
	}
}

// void PrintMark::on_pushButton_26_clicked()
// {
// 	ushort flagstop[1] = { 0, };
// 	flagstop[0] = 1;
// 	smp86xHandler[0]->writeRawData(0x178, 2, (ushort*)flagstop);  //µ×²ãÅÐ¶Ï
// }

void PrintMark::slotTimeout()
{
	if (closeDown)
		return;

	SMP86X_STATUS ss[] = { smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus() };
	labelCom[0]->setStyleSheet((ss[0].axis_status[0].state == 0x80) ? "color:red;" : "color:green");
#ifdef _OLD_VERSION
	labelCom[1]->setStyleSheet((ss[1].axis_status[0].state == 0x80) ? "color:red;" : "color:green");
#endif // _OLD_VERSION

	ui->groupBox_3->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	platform->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	ui->widget_2->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	ui->widget_3->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	conveyor->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	tabWidget->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	ui->pushButton_6->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	ui->pushButton_25->setEnabled(!procFlag.printing_start || procFlag.printing_pause);
	ui->actionRunCpk->setEnabled(!procFlag.printing_start);
	ui->actionSfc->setEnabled(!procFlag.printing_start /*&& ui->checkBox->isChecked()*/ && ui->checkBox_4->isChecked());

	checkError(ss);
	runSignal(ss);
}

void PrintMark::slotRenewCode()
{
	static bool scheduled = false;
	QSettings settings;
	QString _endpoint = settings.value("Sfc/endpoint").toString();
	QString msg;
	const char d[] = "0123456789ABCDEFGHJKLMNPQRSTUWXY";

	if (!settings.value("Code/auto_reset", true).toBool())
	{
		QTimer::singleShot(10000, this, SLOT(slotRenewCode()));
		return;
	}

#ifdef BarcodePrintService
	if (sfcWin->GetTime(_endpoint, msg))
#endif // BarcodePrintService
#ifdef FoxlinkAdd
	msg = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:z");
	if(true)
#endif // FoxlinkAdd
	{
		//addMessage(QString::fromUtf16(L"SFC·þÎñÆ÷Ê±¼äÎª:%1").arg(msg));
		QDateTime dt = QDateTime::fromString(msg, "yyyy-MM-dd hh:mm:ss:z");
		if (scheduled)
		{
			QDate date = dt.date();
			QString prefix = QString("F0P%1%2%3").arg(date.year() - 2010, 0, 16).arg(d[date.month()]).arg(d[date.day()]);
			QString first = settings.value("Code/first").toString();
			QString subfix = settings.value("Code/subfix").toString();
			settings.setValue("Code/prefix", prefix.toUpper());
			settings.setValue("Code/next", first);
			updateStatistics();
			addMessage(QString::fromUtf16(L"ÖØÖÃÁ÷Ë®´a³É¹¦, ÏÂÒ»¸ö±àÂëÎª\"%1\"").arg(prefix.toUpper() + first + subfix));

			QString path = QString::fromLocal8Bit(settings.value("TimeRecord/path").toByteArray());
			QString filePath = (path.isEmpty() ? "." : path) + QDir::separator() + date.addDays(-1).toString(Qt::DefaultLocaleShortDate) + ".txt";
			QFile file(filePath);
			if (file.open(QFile::ReadWrite))
			{
				QTextStream stream(&file);
				stream.setCodec("UTF-8");
				stream << QString::fromUtf16(L"Ç°´ý°åÊ±¼ä×ÜºÍ: %1\r\n").arg(QTime(0, 0, 0, 1).addMSecs(waitForUpChain).toString("HH:mm:ss"));
				stream << QString::fromUtf16(L"ºó´ý°åÊ±¼ä×ÜºÍ: %1\r\n").arg(QTime(0, 0, 0, 1).addMSecs(waitForDownChain).toString("HH:mm:ss"));
				file.close();
				addMessage(QString::fromUtf16(L"´ý°å×ÜÊ±¼ä±£´æµ½\"%1\"").arg(filePath), Qt::darkCyan);
				waitForUpChain = waitForDownChain = 0;
			}
			else
			{
				addMessage(QString::fromUtf16(L"´ý°å×ÜÊ±¼ä±£´æÊ§°Ü, ÎÄ¼þ\"%1\"´´½¨²»³É¹¦").arg(filePath), Qt::red);
			}
		}

		QDateTime dt1 = dt;
		dt1.setTime(QTime(7, 50, 0, 0));
		qint64 ms = dt.msecsTo(dt1);
		if (ms < 0 || scheduled) ms += 24 * 60 * 60 * 1000;
		QTimer::singleShot(ms, this, SLOT(slotRenewCode()));
		//addMessage(QString::fromUtf16(L"%2½«ÔÚ%1ÃëÖ®ºóÖØÖÃÁ÷Ë®´a").arg(ms / 1000).arg(scheduled ? QString::fromUtf16(L"ÏÂÒ»´Î") : ""));
		scheduled = true;
	}
	else
	{
		//addMessage(QString::fromUtf16(L"»ñÈ¡SFC·þÎñÆ÷Ê±¼äÊ§°Ü!"), Qt::red);
		QTimer::singleShot(300000, this, SLOT(slotRenewCode()));
		smp86xHandler[0]->setOutput(2, 0);
		smp86xHandler[0]->setOutput(3, 0);
		//QtConcurrent::run([&](){
		//});
		//
	}
}

void PrintMark::slotCheckExpire()
{
	QSettings settings;
	QString _endpoint = settings.value("Sfc/endpoint").toString();
	QString msg;
	QDate expire(2019, 6, 30);
	QDateTime dt = QDateTime::currentDateTime();
	QDateTime ds = QDateTime::fromTime_t(settings.value("utc", dt.toTime_t()).toUInt());
#ifdef BarcodePrintService
	if (sfcWin->GetTime(_endpoint, msg))
#endif // BarcodePrintService
#ifdef FoxlinkAdd
	if(false)
#endif // FoxlinkAdd
	{
		dt = QDateTime::fromString(msg, "yyyy-MM-dd hh:mm:ss:z");
	}

	if (dt.secsTo(ds) < 0)
		ds = dt;

	int secLeft = dt.secsTo(QDateTime(expire));
	if (secLeft < 0 || dt.secsTo(ds) > 7200)
	{
		smp86xHandler[0]->writeRawBit(0x41, 1);
		smp86xHandler[1]->writeRawBit(0x41, 1);
		settings.setValue("save_close", true);
		QTimer::singleShot(qrand() % 10000, qApp, SLOT(quit()));
		addMessage(QString::fromUtf16(L"½«ÔÚ10ÃëÖ®ºóÖØÖÃ"), Qt::red);
		return;
	}
	settings.setValue("utc", ds.toTime_t()+30);
	//QtConcurrent::run([this](){::Sleep(30000); QMetaObject::invokeMethod(this, SLOT(slotCheckExpire())); });
	QTimer::singleShot(30000, Qt::PreciseTimer, this, SLOT(slotCheckExpire()));
	if (secLeft > 0 && secLeft < 86400)
	{
		static bool bWarned = false;
		if (!bWarned)
		{
			bWarned = true;
			QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"<span style=\"color:red;\">Éè±¸½«ÔÚ24Ð¡Ê±ÄÚ¹ýÆÚ, Çë¼°Ê±ÁªÏµ¹©Ó¦ÉÌ½øÐÐ¸üÐÂ</span>"));
		}
	}
}

void PrintMark::on_pushButton_2_clicked()
{
	QSettings settings;
	QByteArray next = settings.value("Code/next", "0001").toString().toLatin1();
	//QByteArray prefix = settings.value("Code/prefix", "F0P54S").toString().toLatin1();
	//QByteArray subfix = settings.value("Code/subfix", "FY9Y9Z1").toString().toLatin1();

	//next = nextCode(next);
	//settings.setValue("Code/next", QString::fromLatin1(next));
	//ui->lineEdit_2->setText(prefix+next+subfix);
	updateStatistics();
	//time_t t;
	//QString text = ui->lineEdit_2->text();
	//_Database::check(text.toLatin1(), t);
	//int res = QMessageBox::warning(this, QString::fromUtf16(L"·¢ÏÖÖØÂë"), QString::fromUtf16(L"%1\nµÄÉÏ´Î´òÓ¡Ê±¼äÎª:\n%2").arg(text).arg(ctime(&t)), QString::fromUtf16(L"ÏÂÒ»¸ö"), QString::fromUtf16(L"ÔÝÍ£"));
	//QMessageBox::information(this, QString::fromUtf16(L"lll"), QString("%1").arg(res));
}

void PrintMark::on_tableWidget_customContextMenuRequested( const QPoint & pos )
{
	QTableWidgetItem* item = ui->tableWidget->itemAt(pos);
	if(!item) 
		return;

	QAction* action = NULL;
	int row		= ui->tableWidget->row(item);
	int column	= ui->tableWidget->column(item);
	action = QMenu::exec(QList<QAction*>() << ui->actionGetPos << ui->actionGoto << ui->actionTGoto, QCursor::pos());
	if (action == ui->actionGetPos)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		ui->tableWidget->item(row, 1)->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
		ui->tableWidget->item(row, 2)->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
	}
	if (action == ui->actionGoto)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		double x = ui->tableWidget->item(row, column<3 ? 1 :3)->text().toDouble();
		double y = ui->tableWidget->item(row, column<3 ? 2 :4)->text().toDouble();
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss.axis_status[0].logicPos), (y/pulseEquivalent[1] - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
	if (action == ui->actionTGoto)
	{
		QSettings settings;
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		double x = ui->tableWidget->item(row, column<3 ? 1 :3)->text().toDouble();
		double y = ui->tableWidget->item(row, column<3 ? 2 :4)->text().toDouble();
		double dx = settings.value("Offset/ofs_x", "0.000").toDouble();
		double dy = settings.value("Offset/ofs_y", "0.000").toDouble();
		smp86xHandler[0]->start(0, 1, ((x+dx)/pulseEquivalent[0] - ss.axis_status[0].logicPos), ((y+dy)/pulseEquivalent[1] - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
}

void PrintMark::on_tableWidget_2_customContextMenuRequested( const QPoint & pos )
{
	QTableWidgetItem* item = ui->tableWidget_2->itemAt(pos);
	if(!item) 
		return;

	QAction* action = NULL;
	int row		= ui->tableWidget_2->row(item);
	int column	= ui->tableWidget_2->column(item);
	action = QMenu::exec(QList<QAction*>() << ui->actionGetPos << ui->actionGoto, QCursor::pos());
	if (action == ui->actionGetPos)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		ui->tableWidget_2->item(row, 1)->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
		ui->tableWidget_2->item(row, 2)->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
	}
	if (action == ui->actionGoto)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		double x = ui->tableWidget_2->item(row, column<3 ? 1 :3)->text().toDouble();
		double y = ui->tableWidget_2->item(row, column<3 ? 2 :4)->text().toDouble();
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss.axis_status[0].logicPos), (y/pulseEquivalent[1] - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
}

void PrintMark::on_tableWidget_3_customContextMenuRequested( const QPoint & pos )
{
	QTableWidgetItem* item = ui->tableWidget_3->itemAt(pos);
	if(!item) 
		return;

	QAction* action = NULL;
	int column	= ui->tableWidget_3->column(item);
	action = QMenu::exec(QList<QAction*>() << ui->actionGetPos << ui->actionGoto, QCursor::pos());
	if (action == ui->actionGetPos)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		ui->tableWidget_3->item(0, 1)->setText(QString("%1").arg(ss.axis_status[0].logicPos*pulseEquivalent[0], 0, 'f', 3));
		ui->tableWidget_3->item(0, 2)->setText(QString("%1").arg(ss.axis_status[1].logicPos*pulseEquivalent[1], 0, 'f', 3));
	}
	if (action == ui->actionGoto)
	{
		SMP86X_STATUS ss = smp86xHandler[0]->getSmp86xStatus();
		double x = ui->tableWidget_3->item(0, column<2 ? 1 :3)->text().toDouble();
		double y = ui->tableWidget_3->item(0, column<2 ? 2 :4)->text().toDouble();
		smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss.axis_status[0].logicPos), (y/pulseEquivalent[1] - ss.axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
}

void PrintMark::on_pushButton_3_clicked()
{
}

void PrintMark::on_pushButton_14_clicked()
{
	//QString text = ui->lineEdit_2->text();
	//QByteArray buff = genPrintData(text);
	//sendPrintData(device, buff);
	//_Database::deposit(text.toLatin1());
}

void PrintMark::on_pushButton_17_clicked()
{
#ifdef _OLD_VERSION
// 	sendPrintData(device, QByteArray("\x1bOE00000\x04"));
// 	sendPrintData(device, QByteArray("\x1bOE00001\x04"));
// 	sendPrintData(device, QByteArray("\x1bOE00002\x04"));
#endif // _OLD_VERSION
}

void PrintMark::on_pushButton_18_clicked()
{
	procFlag.printing_pause = true;
	smp86xHandler[0]->setOutput(1, 1);
	smp86xHandler[0]->setOutput(2, 0);
 	smp86xHandler[0]->setOutput(0, 1);
}

void PrintMark::runScanCode( SMP86X_STATUS ss[] )
{
	static int _step = 0, _index = 0;
	//static bool codeErr = false;
	static QTime time;
	static QMutex _mutex;
	if (!_mutex.tryLock())
		return;

	_mutex.unlock();
	QMutexLocker l(&_mutex);

	if(!procFlag.scancode_start)
	{
		_step = 0; _index = 0;
		return;
	}

	if(tcpSocket->state() != QAbstractSocket::ConnectedState)
	{
		procFlag.scancode_start = false;
		addMessage(QString::fromUtf16(L"ÊÓ¾õÄ£¿éÎ´¾ÍÐ÷"), Qt::red);
		return;
	}

	if(procFlag.printing_pause)
		return;

	if(isRunning(ss[0]))
		return;

	QSettings settings;
	int delay_code = settings.value("Delay/code", 100).toInt();
	int lastRow = ui->tableWidget->rowCount()-1;
	float x, y, z, u;
	QByteArray readCode;

	switch(_step)
	{
	case 0:
		//smp86xHandler[0]->setPWM(0, settings.value("Light/code", 30).toInt()*255/100);
		printInfo.child_state.clear();
		printInfo.bound_serial = "OK";
		_step = 10;
	case 10:
		if((!ui->checkBox->isChecked() || 
			ui->tableWidget_2->item(lastRow-_index, 0)->checkState() == Qt::Unchecked)
			&& ui->tableWidget->item(lastRow-_index, 0)->checkState() == Qt::Checked)
		{
			double speed = settings.value("Print/speed", 100).toInt()/100.0;
			x = ui->tableWidget->item(lastRow-_index, 3)->text().toDouble();
			y = ui->tableWidget->item(lastRow-_index, 4)->text().toDouble();
			//z = settings.value("Position/mark1_z", 0).toDouble();
			smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1]*speed, speedValue[2]/1000.0);
			//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
			procFlag.real_time = true;
			_step = 20;
			break;
		}
		if(++_index < ui->tableWidget->rowCount())
			break;

		_step = 60;
		break;
	case 20:
		time.restart();
		_step = 30;
		break;
	case 30:
		if(time.elapsed() < delay_code)
			break;

		tcpSocket->readAll();
		tcpSocket->write("check 1");
		tcpSocket->waitForBytesWritten(3000);

#if 0
		QtConcurrent::run([this](){
			if(tcpSocket->waitForReadyRead(3000))
			{
				QMetaObject::invokeMethod(this, "addMessage", Q_ARG(QString, QString::fromUtf16(L"¶þÎ¬Âë½á¹û: %1").arg(tcpSocket->readAll().trimmed().constData())), Q_ARG(QColor, Qt::black));
			}
		});
#else
		tcpSocket->waitForReadyRead(3000);
		readCode = tcpSocket->readAll().trimmed();
		if(ui->tableWidget->item(lastRow-_index, 0)->text().compare(readCode) != 0 && settings.value("Code/compare", true).toBool())
		{
			addMessage(QString::fromUtf16(L"µãÎ»%2¶þÎ¬Âë½á¹û: \"%1\"").arg(readCode.constData()).arg(lastRow-_index+1), Qt::red);
			for (int j=0; j<ui->tableWidget->columnCount(); j++)
				ui->tableWidget->item(lastRow-_index, j)->setBackground(Qt::red);
#ifdef FoxlinkAdd
			printInfo.bound_serial = "NG";
			printInfo.child_state.push_front(QString("%1:EC01").arg(lastRow-_index+1));
#else
#endif // FoxlinkAdd
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			int res = QMessageBox::information(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"¶þÎ¬Âë½á¹ûÒì³£"), QMessageBox::Retry, QMessageBox::Ignore, QMessageBox::Abort);
			sigStat.alarm = 1;
			switch(res)
			{
			case QMessageBox::Retry:
				procFlag.printing_pause = false;
				return;
			case QMessageBox::Ignore:
				procFlag.printing_pause = false;
				break;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				//if (!ui->checkBox_5->isChecked())
				{
					QString lineName = settings.value("Sfc/linename").toString();
					QString strData;
					strData = lineName + ";51;" + strEmployee + ";" + printInfo.panel_no + ";NG;";
					printInfo.child_state.removeAll("OK");
					strData += printInfo.child_state.join("|") + ";";
					//for (int _i = 0; _i < printInfo.child_state.size(); _i++)
					//	if (printInfo.child_state[_i] != "OK")
					//		strData += QString("%1:EC01|").arg(_i + 1);
					//strData.replace(QRegExp("\\|$"), ";");
					SaveTestData(strData);
				}
				break;
			}
		}
		else
		{
#ifdef FoxlinkAdd
			printInfo.child_state.push_front("OK");
#else
			printInfo.child_serial.push_front(readCode);
#endif // FoxlinkAdd
			addMessage(QString::fromUtf16(L"µãÎ»%2¶þÎ¬Âë½á¹û: \"%1\"").arg(readCode.constData()).arg(lastRow-_index+1));
			//¼ÇÂ¼Êý¾Ý
			QString filename = settings.value("General/last").toString();
			filename.replace(QFileInfo(filename).suffix(), "txt");
			QFile file(filename);
// 			QDir::setCurrent(QApplication::applicationDirPath());
// 			file.setFileName("printfdone.txt");
			if (file.open(QFile::WriteOnly|QFile::Append))
			{
				QTextStream out(&file);
				for (int i = 0; i < 7; i++)
				{
					out << ui->tableWidget->item(lastRow - _index, i)->text();
					out << "   ";
				}		
				out << "\r\n";
				file.close();
			}	
		}
#endif // 0

		if(++_index < ui->tableWidget->rowCount())
		{
			_step = 10;
			break;
		}

#ifndef FoxlinkAdd
		_step = 40;
	case 40:
		if(ui->actionSfc->isChecked() && ui->tableWidget_3->item(0, 0)->checkState() == Qt::Checked)
		{
			double speed = settings.value("Print/speed", 100).toInt()/100.0;
			x = ui->tableWidget_3->item(0, 3)->text().toDouble();
			y = ui->tableWidget_3->item(0, 4)->text().toDouble();
			//z = settings.value("Position/mark1_z", 0).toDouble();
			smp86xHandler[0]->start(0, 1, (x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1]*speed, speedValue[2]/1000.0);
			//smp86xHandler[0]->start(1, (y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[3], speedValue[4], speedValue[5]/1000.0);
			//smp86xHandler[0]->start(2, (z/pulseEquivalent[2] - ss[0].axis_status[2].logicPos), speedValue[6], speedValue[7], speedValue[8]/1000.0);
			procFlag.real_time = true;
			_step = 50;
			break;
		}
		printInfo.bound_serial = "";
		_step = 60;
		break;
	case 50:
		time.restart();
		_step = 55;
		break;
	case 55:
		if(time.elapsed() < delay_code)
			break;

#if 0
		tcpSocket->readAll();
		tcpSocket->write("$B*s$E*");
		tcpSocket->waitForBytesWritten(3000);

		tcpSocket->waitForReadyRead(3000);
		readCode = tcpSocket->readAll().trimmed();
		//if(printInfo.panel_no.compare(readCode) != 0  && settings.value("Code/compare", true).toBool())
		if (readCode.isEmpty())
		{
			addMessage(QString::fromUtf16(L"ÖÎ¾ß¶þÎ¬Âë½á¹û: \"%1\"").arg(readCode.constData()), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			int res = QMessageBox::information(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"¶þÎ¬Âë½á¹ûÒì³£"), QMessageBox::Retry, QMessageBox::Ignore, QMessageBox::Abort);
			sigStat.alarm = 1;
			switch(res)
			{
			case QMessageBox::Retry:
				time.restart();
				procFlag.printing_pause = false;
				return;
			case QMessageBox::Ignore:
				procFlag.printing_pause = false;
				break;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				break;
			}
		}
		else
		{
			addMessage(QString::fromUtf16(L"ÖÎ¾ß¶þÎ¬Âë½á¹û: \"%1\"").arg(readCode.constData()));
			printInfo.bound_serial = readCode;
		}
#else
		tcpSocket->readAll();
		tcpSocket->write("$B*b$E*");
		tcpSocket->waitForBytesWritten(3000);

		tcpSocket->waitForReadyRead(3000);
		readCode = tcpSocket->readAll().trimmed();
		if(readCode.isEmpty()) 
			readCode = settings.value("Sfc/bound_serial").toString().toLatin1();
		//if(printInfo.panel_no.compare(readCode) != 0  && settings.value("Code/compare", true).toBool())
		if (readCode.isEmpty())
		{
			addMessage(QString::fromUtf16(L"ÖÎ¾ßÌõÂë½á¹û: \"%1\"").arg(readCode.constData()), Qt::red);
			on_pushButton_18_clicked();
			sigStat.alarm = 0;
			int res = QMessageBox::information(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"ÌõÂë½á¹ûÒì³£"), QMessageBox::Retry, QMessageBox::Ignore, QMessageBox::Abort);
			sigStat.alarm = 1;
			switch (res)
			{
			case QMessageBox::Retry:
				time.restart();
				procFlag.printing_pause = false;
				return;
			case QMessageBox::Ignore:
				procFlag.printing_pause = false;
				break;
			case QMessageBox::Abort:
				on_pushButton_5_clicked();
				break;
			}
		}
		else
		{
			addMessage(QString::fromUtf16(L"ÖÎ¾ßÌõÂë½á¹û: \"%1\"").arg(readCode.constData()));
			printInfo.bound_serial = readCode;
		}
#endif // 0
#endif // FoxlinkAdd
		_step = 60; 
	case 60:
		procFlag.scancode_start = false;
		_step = 0;
		_index = 0;
		break;
	}
}

bool PrintMark::writeBadMark( QString filename )
{
	QSettings settings;
	if(!settings.value("BadMark/enabled", false).toBool())
		return true;

	if(filename.isEmpty())
	{
		QString path = QString::fromLocal8Bit(settings.value("BadMark/path").toByteArray());
		if(path.isEmpty()) path = QDir::currentPath();
		QDir dir(path);
		auto entryList = dir.entryList(QStringList() << ui->lineEdit->text()+"*.xml", QDir::Files, QDir::Name|QDir::Reversed);
		if (entryList.size())
		{
			int index = entryList[0].mid(ui->lineEdit->text().length(), 5).toInt();
			filename = path+"/"+ui->lineEdit->text()+QString("%1").arg(index+1, 5, 10, QChar('0'))+".xml";
		}
		else
		{
			filename = path+"/"+ui->lineEdit->text()+"00001.xml";
		}
	}

	QFile file(filename);
	if(!file.open(QFile::WriteOnly))
		return false;

	int count = 0;
	for (int i=0; i<ui->tableWidget->rowCount(); i++)
	{
		if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
			count++;
	}
	QXmlStreamWriter stream(&file);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();
	stream.writeStartElement("pwb");
	stream.writeStartElement("Mark");
	stream.writeStartElement("BadMark");
	stream.writeStartElement("BadMarkCount");
	stream.writeAttribute("cnt", QString("%1").arg(count));
	stream.writeEndElement(); // BadMarkCount
	count = 0;
	for (int i=0; i<ui->tableWidget->rowCount(); i++)
	{
		if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
		{
			stream.writeStartElement("BadMarkData");
			stream.writeAttribute("num", QString("%1").arg(++count));
			stream.writeTextElement("BadMarkRecResult", (ui->tableWidget_2->item(i, 0)->checkState() == Qt::Checked) ? "1" : "0");
			stream.writeEndElement(); // BadMarkData
		}
	}
	stream.writeEndElement(); // BadMark
	stream.writeEndElement(); // Mark
	stream.writeEndElement(); // pwb
	file.close();
	return true;
}

bool PrintMark::SaveTestData(const QString & strData)
{
#ifdef FoxlinkAdd
	QSettings settings;
	int ws_mode = settings.value("SFC/mode", 1).toInt();
	QString msg;
	QString _endpoint = settings.value("Sfc/endpoint").toString();
	if (ws_mode == 0)
		sfcWin->SwSendData(strData, msg);
	else
		sfcWin->SaveTestData(_endpoint, strData, msg);
	if (msg.mid(0, 2) != "OK")
	{
		/*QMessageBox::information(this, QString::fromUtf16(L"SFC´íÎó"), msg, QMessageBox::Ok);*/
		return false;
	}
#endif // FoxlinkAdd
	return true;
}

void PrintMark::updateStatistics()
{
	QSettings settings;
	QString ink_data = NULL;
	QString ink_data2 = NULL;
	int total = settings.value("Code/total", "0").toInt();
	int num = settings.value(QString("ink_printf%1/text_number").arg(curPrintf), 0).toInt();
	//int num2 = settings.value("ink_2/text_number", 0).toInt();
	int donecout;
	QByteArray code,first,code2;
	int codelen = settings.value(QString("ink_printf%1/codenum").arg(curPrintf), "4").toInt();
	QByteArray c = settings.value(QString("ink_printf%1/countcode").arg(curPrintf), "0123456789").toByteArray();
	first = settings.value(QString("ink_printf%1/first").arg(curPrintf), 0000).toString().remove(0,2).toLatin1();
	if (num != 0)
	{
		ink_data = timrChange(num, "ink_printf",code);
	}
	if (chushi == 1)
	{
		count = 0;
		for (int i = codelen - 1; i >= 0; i--)
		{
			if (first[i] == code[i]);
			else
				if ((c.indexOf(code[i]) - c.indexOf(first[i])) < 0)
				{
					int ww = c.size() + c.indexOf(code[i]) - c.indexOf(first[i]);
					count = count + ww*pow(c.size(), codelen - i - 1) - pow(c.size(), codelen - i);
				}
				else
				{
					int ww = c.indexOf(code[i]) - c.indexOf(first[i]);
					count = count + ww*pow(c.size(), codelen - i - 1);
				}
		}
		int StepLong = settings.value(QString("ink_printf%1/Step").arg(curPrintf), 1).toInt();
		int count_Step = settings.value(QString("ink_printf%1/Step_current").arg(curPrintf), 1).toInt();
		count = count*StepLong + count_Step - 1;
		chushi = 0;
	}
	else
		count++;
CUR:
	ui->lcdNumber->display(total);
	ui->lcdNumber_2->display(count);
	ui->lcdNumber_3->display(total - count);
	ui->lineEdit_2->setText(ink_data);
	//ui->lineEdit_3->setText(ink_data2);
#ifdef _FOXLINK
	ui->lineEdit_2->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, "
		"stop:0 rgba(255, 255, 255, 255), stop:0.435 rgba(255, 255, 255, 255), stop:0.436 rgba(255, 0, 0, 64), "
		"stop:0.61 rgba(255, 0, 0, 64), stop:0.611 rgba(255, 255, 255, 255), stop:1 rgba(255, 255, 255, 255));");
#else
	ui->lineEdit_2->setStyleSheet("");
#endif // _FOXLINK

	if (total - count <= 0)
	{
		addMessage(QString::fromUtf16(L"¶þÎ¬ÂëÐòÁÐÒÑÓÃÍê!"), Qt::red);
		on_pushButton_18_clicked();
		procFlag.code_empty_err = true;
		sigStat.alarm = 0;
	}
}

QString PrintMark::timrChange(int num, QString text,QByteArray &code)
{
	QSettings settings;
	QString datatemp = NULL;
	int codelen = settings.value(QString("ink_printf%1/codenum").arg(curPrintf), "4").toInt();
	QByteArray c = settings.value(QString("ink_printf%!/countcode").arg(curPrintf), "0123456789").toByteArray();
	for (int i = 0; i < num; i++)
	{
		QString TC = settings.value(QString("%1%2/text%3").arg(text).arg(curPrintf).arg(i)).toString();
		if (TC.startsWith("T"))
		{
			TC.remove(0, 2);
			QString ttt = QDateTime::currentDateTime().toString("yyyy.MM.dd");
			QString tt = QDateTime::currentDateTime().toString("yy.MM.dd");
			QString t = QDateTime::currentDateTime().toString("MM.dd");
			int pos;
			QRegExp rx("\\.");
			switch (TC.size())
			{
			case 4:
				pos = 0;
				while ((pos = rx.indexIn(t, pos)) != -1)
				{
					t = t.remove(pos, 1);
					pos = rx.matchedLength();
				}
				TC = t;
				break;
			case 6:
				pos = 0;
				while ((pos = rx.indexIn(tt, pos)) != -1)
				{
					tt = tt.remove(pos, 1);
					pos = rx.matchedLength();
				}
				TC = tt;
				break;
			case 8:
				pos = 0;
				while ((pos = rx.indexIn(ttt, pos)) != -1)
				{
					ttt = ttt.remove(pos, 1);
					pos = rx.matchedLength();
				}
				TC = ttt;
				break;
			default:
				break;
			}
			datatemp = datatemp.append(TC);
			settings.setValue(QString("%1%2/text%3").arg(text).arg(curPrintf).arg(i), QString("T ").append(TC));
		}
		else if (TC.startsWith("N"))
		{
			int count_Step = settings.value(QString("%1%2/Step_current").arg(text).arg(curPrintf).arg(i),1).toInt();
			int StepLong = settings.value(QString("%1%2/Step").arg(text).arg(curPrintf).arg(i), 1).toInt();
			code = TC.remove(0, 2).toLatin1();
			QByteArray newCode(codelen, c[0]);
			if (chushi == 1)
			{
				datatemp = datatemp.append(code);
				continue;
			}
			if (count_Step < StepLong)
			{
				datatemp = datatemp.append(code);
				count_Step++;
				settings.setValue(QString("%1%2/Step_current").arg(text).arg(curPrintf).arg(i), count_Step);
				continue;
			}
			int carry = 1;
			for (int i = codelen - 1; i >= 0; i--)
			{
				int p = c.indexOf(code[i]);
				newCode[i] = c[((p + carry) % c.size())];
				carry = (p + carry) / c.size();
			}
			//reset count_Step
			settings.setValue(QString("%1%2/Step_current").arg(text).arg(curPrintf).arg(i), 1);
			datatemp = datatemp.append(newCode);
			settings.setValue(QString("%1%2/text%3").arg(text).arg(curPrintf).arg(i), QString("N ").append(newCode));
		}
		else
		{
			datatemp = datatemp.append(TC.remove(0, 2));
		}
	}
	return datatemp;
}

void PrintMark::runSignal( SMP86X_STATUS ss[] )
{
	static SIGSTAT _s = sigStat;
	static int c = 0;

	if(procFlag.printing_start && !procFlag.printing_pause)
		sigStat.yellow = 1, sigStat.green = 0;//(c++%16)/8;
	else if(ui->listWidget_2->count() == 0)
		sigStat.yellow = 1, sigStat.green = 0;
	else
		sigStat.yellow = 0, sigStat.green = 1;

	sigStat.red &= sigStat.alarm;
#ifdef _OLD_VERSION
	if(sigStat.red != _s.red)
		smp86xHandler[0]->setOutput(8, sigStat.red);
	if(sigStat.alarm != _s.alarm)
		smp86xHandler[0]->setOutput(9, sigStat.alarm);
	if(sigStat.yellow != _s.yellow)
		smp86xHandler[0]->setOutput(10, sigStat.yellow);
	if(sigStat.green != _s.green)
		smp86xHandler[0]->setOutput(11, sigStat.green);
#else
	if(sigStat.red != _s.red)
		smp86xHandler[0]->setOutput(18, sigStat.red);
	if(sigStat.alarm != _s.alarm)
		smp86xHandler[0]->setOutput(18, sigStat.alarm);
	if(sigStat.yellow != _s.yellow)
		smp86xHandler[0]->setOutput(19, sigStat.yellow);
	if(sigStat.green != _s.green)
		smp86xHandler[0]->setOutput(20, sigStat.green);
#endif // _OLD_VERSION
	memcpy(&_s, &sigStat, sizeof(SIGSTAT));
}

// void PrintMark::on_actionImport_triggered()
// {
// 	if (isWindowModified())
// 	{
// 		int respond = QMessageBox::information(this, QString::fromUtf16(L"ÌáÊ¾"), QString::fromUtf16(L"·½°¸±»ÐÞ¸Ä,ÊÇ·ñÒª±£´æ·½°¸?"), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
// 		switch (respond)
// 		{
// 		case QMessageBox::Cancel:
// 			return;
// 		case QMessageBox::Save:
// 			on_actionSave_triggered();
// 			break;
// 		case  QMessageBox::Discard:
// 			break;
// 		}
// 	}
// 
// 	QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf16(L"µ¼ÈëÊý¾Ý"), "", QString::fromUtf16(L"ExcelÎÄ¼þ(*.xls)"));
// 	if (!fileName.isEmpty())
// 	{
// 		ImportData data;
// 		if (QFileInfo(fileName).suffix() == "xls")
// 		{
// 			int ret = readExcelData(fileName.toLocal8Bit().constData(), data);
// 			if (ret != 0)
// 				return;
// 		}
// 
// 		//ui->lineEdit->setText(data.n);
// 		ui->tableWidget->clearContents();
// 		ui->tableWidget->setRowCount(data.p.size());
// 		ui->tableWidget_2->clearContents();
// 		ui->tableWidget_2->setRowCount(data.b.size());
// 		markData[0].curntPos = markData[0].firstPos = QVector3D(QVector2D(data.m[0]), 1);
// 		markData[1].curntPos = markData[1].firstPos = QVector3D(QVector2D(data.m[1]), 1);
// 		ui->label_4->setText(QString("%1 %2 %3").arg(markData[0].firstPos.x()).arg(markData[0].firstPos.y()).arg(markData[0].firstPos.z()));
// 		ui->label_5->setText(QString("%1 %2 %3").arg(markData[1].firstPos.x()).arg(markData[1].firstPos.y()).arg(markData[1].firstPos.z()));
// 		ui->label_4->setToolTip(ui->label_4->text());
// 		ui->label_5->setToolTip(ui->label_5->text());
// 		for (int p=0; p<data.p.size(); p++)
// 		{
// 			int row = p;
// 			for(int k=0; k<ui->tableWidget->columnCount(); k++)
// 			{
// 				QTableWidgetItem* item = new QTableWidgetItem;
// 				item->setTextAlignment(Qt::AlignCenter);
// 				ui->tableWidget->setItem(row, k, item);
// 			}
// 
// 			ui->tableWidget->item(row, 0)->setCheckState(Qt::Checked);
// 			ui->tableWidget->item(row, 0)->setText("");
// 			ui->tableWidget->item(row, 1)->setText(QString("%1").arg(data.p[p].x(), 0, 'f', 3));
// 			ui->tableWidget->item(row, 2)->setText(QString("%1").arg(data.p[p].y(), 0, 'f', 3));
// 			ui->tableWidget->item(row, 3)->setText("");
// 			ui->tableWidget->item(row, 4)->setText("");
// 			ui->tableWidget->item(row, 5)->setText("0");
// 			ui->tableWidget->item(row, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
// 			ui->tableWidget->item(row, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
// 
// 			for (int k = 0; k<ui->tableWidget_2->columnCount(); k++)
// 			{
// 				QTableWidgetItem* item = new QTableWidgetItem;
// 				item->setTextAlignment(Qt::AlignCenter);
// 				ui->tableWidget_2->setItem(row, k, item);
// 			}
// 			ui->tableWidget_2->item(row, 0)->setCheckState(Qt::Unchecked);
// 			ui->tableWidget_2->item(row, 0)->setFlags(ui->tableWidget_2->item(row, 0)->flags()&(~Qt::ItemIsUserCheckable));
// 			ui->tableWidget_2->item(row, 1)->setText(QString("%1").arg(data.b[p].x(), 0, 'f', 3));
// 			ui->tableWidget_2->item(row, 2)->setText(QString("%1").arg(data.b[p].y(), 0, 'f', 3));
// 			ui->tableWidget_2->item(row, 3)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
// 			ui->tableWidget_2->item(row, 4)->setBackground(QBrush(qRgb(0xE0, 0xE0, 0xE0)));
// 			ui->tableWidget_2->show();
// 			ui->checkBox->setChecked(true);
// 		}
// 
// 		setWindowModified(true);
// 		setWindowFilePath(QString());
// 		setWindowTitle(QString::fromUtf16(L"×Ô¶¯ÅçÂëÏµÍ³ - Î´±£´æ[*]"));
// 	}
// }

void PrintMark::on_tableWidget_cellChanged(int row, int column) 
{
	switch(column)
	{
	case 1:
	case 2:
	case 5:
		if (column == 5)
		{
			QtConcurrent::run([this]() {
				Sleep(50);
				drawToAngel();
			});
			/*		if (ui->tableWidget->item(row, 5)->text().toInt() == 0)
					{
						for (int i=0;i<ui->tableWidget->columnCount();i++)
						{
							ui->tableWidget->item(row, i)->setBackground(QColor("#FFFFFF"));
						}
					}
					if (ui->tableWidget->item(row, 5)->text().toInt() == 90)
					{
						for (int i = 0; i < ui->tableWidget->columnCount(); i++)
						{
							ui->tableWidget->item(row, i)->setBackground(QColor("#FFF59D"));
						}
					}
					if (ui->tableWidget->item(row, 5)->text().toInt() == 180)
					{
						for (int i = 0; i < ui->tableWidget->columnCount(); i++)
						{
							ui->tableWidget->item(row, i)->setBackground(QColor("#FFFB3B"));
						}
					}
					if (ui->tableWidget->item(row, 5)->text().toInt() == 270)
					{
						for (int i = 0; i < ui->tableWidget->columnCount(); i++)
						{
							ui->tableWidget->item(row, i)->setBackground(QColor("#AED581"));
						}
					}*/
		}
		setWindowModified(true);
		break;
	}
}

void PrintMark::on_tableWidget_2_cellChanged(int row, int column) 
{
	switch(column)
	{
	case 1:
	case 2:
		setWindowModified(true);
		break;
	}
}

void PrintMark::on_tableWidget_3_cellChanged( int row, int column )
{
	switch(column)
	{
	case 0:
	case 1:
		setWindowModified(true);
		break;
	}
}

void PrintMark::on_lineEdit_editingFinished()
{
	setWindowModified(true);
}

void PrintMark::on_actionReadCode_triggered()
{
	if(tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
		tcpSocket->readAll();
		tcpSocket->write("check 1");
		tcpSocket->waitForBytesWritten(3000);
		tcpSocket->waitForReadyRead(3000);
		if(tcpSocket->bytesAvailable() > 1)
		{
			addMessage(QString::fromUtf16(L"¶þÎ¬Âë½á¹û: \"%1\"").arg(tcpSocket->readAll().trimmed().constData()));
			return;
		}

		tcpSocket->readAll();
		tcpSocket->write("check 1");
		tcpSocket->waitForBytesWritten(3000);
		tcpSocket->waitForReadyRead(3000);
		if(tcpSocket->bytesAvailable() > 1)
		{
			addMessage(QString::fromUtf16(L"ÌõÂë½á¹û: \"%1\"").arg(tcpSocket->readAll().trimmed().constData()));
			return;
		}
	}
	addMessage(QString::fromUtf16(L"¶ÁÈ¡¶þÎ¬ÂëÊ§°Ü"), Qt::red);
}

void PrintMark::on_actionGotoCenter_triggered()
{
	float x, y, u;
	if(_visionPos(x, y, u, 0))
	{
		SMP86X_STATUS ss[] = {smp86xHandler[0]->getSmp86xStatus(), smp86xHandler[1]->getSmp86xStatus()};
		double _x = (x+ss[0].axis_status[0].logicPos*pulseEquivalent[0]);
		double _y = (y+ss[0].axis_status[1].logicPos*pulseEquivalent[1]);
		smp86xHandler[0]->start(0, 1, (_x/pulseEquivalent[0] - ss[0].axis_status[0].logicPos), (_y/pulseEquivalent[1] - ss[0].axis_status[1].logicPos), speedValue[0], speedValue[1], speedValue[2]/1000.0);
	}
	else
	{
		addMessage(QString::fromUtf16(L"»ñÈ¡Ä£°åÖÐÐÄÊ§°Ü"), Qt::red);
	}
}

void PrintMark::on_actionTestBadMark_triggered()
{
	float x, y, u;
	addMessage(QString::fromUtf16(L"»µµã²âÊÔ½á¹û: %1").arg(visionValid() ? "OK" : "NG"));
	if (ui->comboBox->currentIndex() == 1)
		if (_visionPos(x, y, u, 2))
			addMessage(QString::fromUtf16(L"°×ÓÍ¶¨Î»½á¹û: %1, %2").arg(x, 0, 'f', 3).arg(y, 0, 'f', 3));
		else
			addMessage(QString::fromUtf16(L"°×ÓÍ¶¨Î»Ê§°Ü"));
}

void PrintMark::on_actionSfc_triggered( bool checked )
{
	QSettings settings;
	settings.setValue("Sfc/enabled", checked);
	if(!checked) sfcWin->hide();
	//ui->checkBox->setEnabled(!checked && ui->pushButton_12->isChecked());
	ui->checkBox_4->setEnabled(!checked && ui->pushButton_12->isChecked());
	ui->tableWidget_3->setVisible(checked);
	setWindowModified(true);
}

void PrintMark::on_actionMaintain1_triggered(bool checked)
{
	QSettings settings;
	QString _station = settings.value("SFC/linename").toString();
	if (!SaveTestData(_station + ";30;" + strEmployee + ";2;"))
	{
		/*QMessageBox::information(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"¼ÇÂ¼±£Ñø¿ªÊ¼Ê§°Ü\n"), QMessageBox::Ok);*/
	}
}

void PrintMark::on_actionMaintain2_triggered(bool checked)
{
	QSettings settings;
	QString _station = settings.value("SFC/linename").toString();
	if (!SaveTestData(_station + ";30;" + strEmployee + ";22;"))
	{
		/*QMessageBox::information(this, QString::fromUtf16(L"SFC´íÎó"), QString::fromUtf16(L"¼ÇÂ¼±£ÑøÍê³ÉÊ§°Ü\n"), QMessageBox::Ok);*/
	}
}

void PrintMark::on_actiondpyBattery_triggered()
{
	if (smp86xHandler[2]->isOpen() /*&& smp86xHandler[3]->isOpen()*/)
	{
		pyBattery* py = new pyBattery(smp86xHandler[2],smp86xHandler[3]);
		py->show();
		py->raise();
		return;
	}
	smp86xHandler[2]->quit();
// 	smp86xHandler[3]->quit();
// 	QtConcurrent::run([this]() {
// 		Sleep(500);
// 		QSettings settings;
// 		QString comport = settings.value("electricity/com", "COM1").toString();
// 		smp86xHandler[2] = new Smp86xHandler(comport, 1);
// 		QString comport2 = settings.value("AirPressure/com", "COM2").toString();
// 		smp86xHandler[3] = new Smp86xHandler(comport2, 2);
// 	});
	QMessageBox::warning(this, QString::fromUtf16(L"¾¯¸æ"), QString::fromUtf16(L"´®¿ÚÎÞ·¨´ò¿ª"));
}

void PrintMark::on_actionSfcWin_triggered()
{
	sfcWin->show();
	sfcWin->setWindowState((sfcWin->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}


//////////////////////////////////////////////////////////////////////////
MyItemDelegate::MyItemDelegate( QObject* parent /*= 0*/ )
{
}

QWidget * MyItemDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
//#ifdef _FOXLINK
	if (index.column() == 6)
	{
		QComboBox* comboBox = new QComboBox(parent);
		comboBox->addItems(QStringList() << "001" << "002" << "003" << "004" << "005");
		return comboBox;
	}
//#endif // _FOXLINK
	if (index.column() == 5)
	{
		QComboBox* comboBox2 = new QComboBox(parent);
		comboBox2->addItems(QStringList() << "0" << "90" << "180" << "270");
		return comboBox2;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void MyItemDelegate::setEditorData( QWidget *editor, const QModelIndex &index ) const
{
//#ifdef _FOXLINK
	if (index.column() == 6)
	{
		QComboBox* comboBox2 = qobject_cast<QComboBox*>(editor);
		comboBox2->setCurrentIndex(comboBox2->findText(index.model()->data(index).toString()));
		comboBox2->showPopup();
	}
//#endif // _FOXLINK
	if (index.column() == 5)
	{
		QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
		comboBox->setCurrentIndex(comboBox->findText(index.model()->data(index).toString()));
		comboBox->showPopup();
	}
	return QStyledItemDelegate::setEditorData(editor, index);
}

void MyItemDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
//#ifdef _FOXLINK
	if (index.column() == 6)
	{
		QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
		model->setData(index, comboBox->currentText());
		return;
	}
//#endif // _FOXLINK
	if (index.column() == 5)
	{
		QComboBox* comboBox2 = qobject_cast<QComboBox*>(editor);
		model->setData(index, comboBox2->currentText());
		return;
	}
	return QStyledItemDelegate::setModelData(editor, model, index);
}

void MyItemDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}
