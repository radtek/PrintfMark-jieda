#ifndef IOMONITOR_H
#define IOMONITOR_H

#include <QWidget>
namespace Ui {class IoMonitor;};
class Smp86xHandler;

class IoMonitor : public QWidget
{
	Q_OBJECT

public:
	IoMonitor(Smp86xHandler* _smp86xHandler, QWidget *parent = 0);
	~IoMonitor();

	void setLabels(const QString& labelFile);
	void setHandler(Smp86xHandler* smp86xHandler){
		this->smp86xHandler = smp86xHandler;
	}
protected slots:
	void on_buttonGroup_buttonClicked ( QAbstractButton * button );
	void on_buttonGroup_buttonPressed ( QAbstractButton * button );
	void on_buttonGroup_buttonReleased ( QAbstractButton * button );
	void on_checkBox_clicked(bool checked);
	void slotTimeout();

private:
	Ui::IoMonitor *ui;
	Smp86xHandler* smp86xHandler;
};

#endif // IOMONITOR_H
