#ifndef SFCWIN_H
#define SFCWIN_H

#include <QWidget>
#include "ui_sfcwin.h"
#include "stdsoap2.h"
#ifdef BarcodePrintService
#include "soapBarcodePrintServiceSoap11BindingProxy.h"
#endif // _DEBUG

#ifdef FoxlinkAdd
#include "soapBasicHttpBinding_USCOREIFoxlinkAddProxy.h"
#endif // _DEBUG

namespace Ui { class SfcWin; };

class SfcWin : public QWidget
{
	friend class PrintMark;
	Q_OBJECT
	
public:
	SfcWin(QWidget *parent = 0);
	~SfcWin();

#ifdef BarcodePrintService
	bool GetTime(const QString& _endpoint, QString& _msg);
	bool FinishPrintInfo(const QString& _endpoint, const QString& _order, const QString& _panel, const QString& _serial, const QString& _bound, QString& _msg);
#endif // _DEBUG
#ifdef FoxlinkAdd
	bool SaveTestData(const QString& _endpoint, const QString& strData, QString& _msg);
	bool SwSendData(const QString& strData, QString& _msg);
#endif // _DEBUG
	bool parsePrintInfo(const QString& text, PRINTINFO& info);
protected slots:
	void on_lineEdit_editingFinished();
	void on_lineEdit_4_editingFinished();
	void on_lineEdit_5_editingFinished();
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
private:
	Ui::SfcWin *ui;
};

#endif // SFCWIN_H
