#include "stdafx.h"
#include "sfcwin.h"

#ifdef BarcodePrintService
#include "BarcodePrintServiceSoap11Binding.nsmap"
#endif
#ifdef FoxlinkAdd
#include "BasicHttpBinding_USCOREIFoxlinkAdd.nsmap"
#endif // _DEBUG

#ifdef BarcodePrintService
bool SfcWin::GetTime(const QString& _endpoint, QString& _msg)
{
	bool ret = true;
	int err = SOAP_OK;
	auto future = QtConcurrent::run([&]()
	{
			BarcodePrintServiceSoap11BindingProxy service(SOAP_C_UTFSTRING);
			_ns1__GetTimeResponse response;
			_ns1__GetTime info;
			if ((err = service.GetTime(_endpoint.toLatin1(), NULL, &info, response)) == SOAP_OK)
			{
				_msg = QString::fromUtf8(response.return_->c_str());
			}
			else
			{
				char buff[4096];
				service.soap_sprint_fault(buff, 4096);
				_msg = QString::fromLocal8Bit(buff);
				ret = false;
				//QMessageBox::information(this, QString::fromUtf16(L"SFC"), QString::fromUtf16(L""));
			}
			service.destroy(); // dealloc serialization and temp data
	});
	while (future.isRunning())
	{
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
	ui->textEdit->setPlainText((ret ? "RETURN:\n" : QString("ERROR:%1\n").arg(err)) + _msg);
	return ret;
}

bool SfcWin::FinishPrintInfo(const QString& _endpoint, const QString& _order, const QString& _panel, const QString& _serial, const QString& _bound, QString& _msg)
{
	std::string workOrder = _order.toUtf8();
	std::string panelNo = _panel.toUtf8();
	std::string serial = _serial.toUtf8();
	std::string bound = _bound.toUtf8();

	BarcodePrintServiceSoap11BindingProxy service(SOAP_C_UTFSTRING);
	_ns1__FinishPrintInfo info;
	_ns1__FinishPrintInfoResponse response;
	info.workOrder_USCOREno = &workOrder;
	info.StationName = &panelNo;
	info.children_USCOREserial = &serial;
	info.bound_USCOREserial = &bound;
	bool ret = true;
	int err = SOAP_OK;

	if ((err = service.FinishPrintInfo(_endpoint.toLatin1(), NULL, &info, response)) == SOAP_OK)
	{
		//QTextCodec* tc = QTextCodec::codecForName("Big5");
		//_msg = response.return_->c_str();
		//_msg += tc->toUnicode(response.return_->c_str());
		_msg = QString::fromUtf8(response.return_->c_str());
		//_msg += QString::fromLatin1(response.return_->c_str());
		//_msg += "\n";
		//for (int i = 0; i < response.return_->length(); i++)
		//{
		//	_msg += QString("%1 ").arg(uchar(response.return_->c_str()[i]), 2, 16, QChar('0'));
		//	if (i % 8 == 7) _msg += "\n";
		//}
		//QFile f("r.txt");
		//f.open(QFile::WriteOnly|QFile::Append);
		//QDataStream s(&f);
		//s.writeBytes(response.return_->c_str(), response.return_->size());
		//f.close();
		ret = true;
	}
	else
	{
		char buff[4096];
		service.soap_sprint_fault(buff, 4096);
		_msg = QString::fromLocal8Bit(buff);
		ret = false;
	}
	service.destroy(); // dealloc serialization and temp data
	ui->textEdit->setPlainText((ret ? "RETURN:\n" : QString("ERROR:%1\n").arg(err)) + _msg);
	return ret && _msg.startsWith("OK");
}

bool SfcWin::parsePrintInfo(const QString& text, PRINTINFO& info)
{
	if (!text.startsWith("OK"))
		return false;

	QStringList strs = text.split(";", QString::SkipEmptyParts);
	if (strs.size() < 3)
		return false;

	info.panel_no = strs[1];
	info.child_serial = QStringList();
	info.index = 0;
	for (int i = 2; i < strs.size(); i++)
	{
		info.child_serial << strs[i];
	}
	return true;
}
#endif // BarcodePrintService

#ifdef FoxlinkAdd
bool SfcWin::SaveTestData(const QString& _endpoint, const QString& strData, QString& _msg)
{
	bool ret = true;
	int err = SOAP_OK;
	std::string _strData = strData.toUtf8();
	auto future = QtConcurrent::run([&]()
	{
		BasicHttpBinding_USCOREIFoxlinkAddProxy service(SOAP_C_UTFSTRING);
		_tempuri__SaveTestDataResponse response;
		_tempuri__SaveTestData info;
		info.strData = &_strData;
		if ((err = service.SaveTestData(_endpoint.toLatin1(), NULL, &info, response)) == SOAP_OK)
		{
			_msg = QString::fromUtf8(response.SaveTestDataResult->c_str());
		}
		else
		{
			char buff[4096];
			service.soap_sprint_fault(buff, 4096);
			_msg = QString::fromLocal8Bit(buff);
			ret = false;
			//QMessageBox::information(this, QString::fromUtf16(L"SFC"), QString::fromUtf16(L""));
		}
		service.destroy(); // dealloc serialization and temp data
	});
	while (future.isRunning())
	{
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
	ui->textEdit->setPlainText((ret ? "RETURN:\n" : QString("ERROR:%1\n").arg(err)) + _msg);
	return ret;
}

bool _Call_SwSendData(const QString & strData, QString & _msg)
{
	auto hHandle = ::LoadLibraryW(L"SwATE_Sckt.dll");
	if(hHandle == INVALID_HANDLE_VALUE)
	{
		_msg = QString::fromUtf16(L"加载SwATE_Sckt.dll失败");
		return false;
	}
	auto f = (bool (WINAPI*)(int, void*, int*))GetProcAddress(hHandle, "SwSendData");
	if (!f)
	{
		_msg = QString::fromUtf16(L"定位函数SwSendData地址失败");
		::FreeLibrary(hHandle); 
		return false; 
	}

	char buff[4096] = "";
	int len = 0;
	QByteArray _strData = strData.toUtf8();
	memcpy(buff, _strData.constData(), _strData.size());
	len = _strData.size();
	try
	{
		bool ret = f(99, buff, &len);
		_msg = QString::fromUtf8(QByteArray(buff, len));
		::FreeLibrary(hHandle);
		return ret;
	}
	catch (...)
	{
		_msg = QString::fromUtf16(L"执行函数SwSendData发生异常");
		::FreeLibrary(hHandle);
		return false;
	}
}

bool SfcWin::SwSendData(const QString & strData, QString & _msg)
{
	bool ret = _Call_SwSendData(strData, _msg);
	ui->textEdit->setPlainText((ret ? "RETURN:\n" : QString("ERROR:\n")) + _msg);
	return ret;
}

bool SfcWin::parsePrintInfo(const QString& text, PRINTINFO& info)
{
	if (!text.startsWith("OK"))
		return false;

	QStringList strs = text.split(QRegExp("[;|:]"), QString::SkipEmptyParts);
	if(strs.size()<2)
		return false;

	info.child_serial = QStringList();
	info.index = 0;
	for(int i=1; i<strs.size(); i++)
	{
		info.child_serial << strs[i];
	}
	return true;
}
#endif // FoxlinkAdd

SfcWin::SfcWin(QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::SfcWin)
{
	ui->setupUi(this);
	ui->label_4->hide();
	ui->lineEdit_2->hide();
	QSettings settings;
	ui->lineEdit->setText(settings.value("Sfc/order_no").toString());
	ui->lineEdit_4->setText(settings.value("Sfc/bound_serial").toString());
	ui->lineEdit_5->setText(settings.value("Sfc/station_name").toString());
#ifdef FoxlinkAdd
	ui->label->setText(QString::fromUtf16(L"機臺編號"));
	ui->label_8->setText(QString::fromUtf16(L"執行代碼"));
	ui->label_6->setText(QString::fromUtf16(L"特殊數據"));
	ui->pushButton->setText("SaveTestData");
	ui->pushButton_2->setText("SwSendData");
#endif
}

SfcWin::~SfcWin()
{
	delete ui;
}

void SfcWin::on_lineEdit_editingFinished()
{
	QSettings settings;
	settings.setValue("Sfc/order_no", ui->lineEdit->text());
}

void SfcWin::on_lineEdit_4_editingFinished()
{
	QSettings settings;
	settings.setValue("Sfc/bound_serial", ui->lineEdit_4->text());
}

void SfcWin::on_lineEdit_5_editingFinished()
{
	QSettings settings;
	settings.setValue("Sfc/station_name", ui->lineEdit_5->text());
}

void SfcWin::on_pushButton_clicked()
{
#ifdef BarcodePrintService
	QSettings settings;
	QString msg;
	QString _endpoint = settings.value("Sfc/endpoint").toString();

	bool ret = GetTime(_endpoint, msg);
	//BarcodePrintServiceSoap11BindingProxy service(SOAP_C_UTFSTRING);
	//_ns1__GetTimeResponse response;
	//_ns1__GetTime info;
	//int err = SOAP_OK;
	//if ((err = service.GetTime(_endpoint.toLatin1(), NULL, &info, response)) == SOAP_OK)
	//{
	//	ui->textEdit->setPlainText("RETURN:\n" + QString::fromUtf8(response.return_->c_str()));
	//}
	//else
	//{
	//	char buff[4096];
	//	service.soap_sprint_fault(buff, 4096);
	//	ui->textEdit->setPlainText(QString("ERROR:%1\n").arg(err) + QString::fromLocal8Bit(buff));
	//}
#endif // BarcodePrintService
#ifdef FoxlinkAdd
	QSettings settings;
	QString msg;
	QString _endpoint = settings.value("Sfc/endpoint").toString();
	QString strData = ui->lineEdit->text() + ";" + ui->lineEdit_5->text() + ";" + ui->lineEdit_4->text() + ";";

	bool ret = SaveTestData(_endpoint, strData, msg);

#endif // FoxlinkAdd

}

void SfcWin::on_pushButton_2_clicked()
{
#ifdef BarcodePrintService
	QSettings settings;
	QString endpoint = settings.value("Sfc/endpoint").toString();
	QString msg;

	bool ret = FinishPrintInfo(endpoint, ui->lineEdit->text(), ui->lineEdit_5->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), msg);
#endif // BarcodePrintService
#ifdef FoxlinkAdd
	QString msg;
	QString strData = ui->lineEdit->text() + ";" + ui->lineEdit_5->text() + ";" + ui->lineEdit_4->text() + ";";

	bool ret = SwSendData(strData, msg);
#endif // FoxlinkAdd
}

