#ifndef OFFSETSETUP_H
#define OFFSETSETUP_H

#include <QWidget>
namespace Ui {class OffsetSetup;};
class Smp86xHandler;

class OffsetSetup : public QWidget
{
	Q_OBJECT

public:
	OffsetSetup(Smp86xHandler* sh, QTcpSocket* tcp1, QWidget *parent = 0);
	~OffsetSetup();

	void setHandler(Smp86xHandler* smp86xHandler){
		this->smp86xHandler = smp86xHandler;
	}
protected slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_buttonBox_clicked(QAbstractButton * button);
private:
	Ui::OffsetSetup *ui;
	Smp86xHandler* smp86xHandler;
	QTcpSocket* tcpSocket;
};

#endif // OFFSETSETUP_H
