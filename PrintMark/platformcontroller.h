#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H

#include <QWidget>
namespace Ui {
	class PlatformController;
	class PlatformController2;
	class PlatformController3;
};
class Smp86xHandler;

class PlatformController : public QWidget
{
	Q_OBJECT

public:
	PlatformController(Smp86xHandler* _smp86xHandler[], QWidget *parent = 0);
	~PlatformController();

	void setHandler(Smp86xHandler* smp86xHandler[2]){
		this->smp86xHandler[0] = smp86xHandler[0];
		this->smp86xHandler[1] = smp86xHandler[1];
	}
	//void setSlave(int slave){this->slave = slave;}
	Q_SIGNAL void reset();
	Ui::PlatformController *ui;
protected slots:
	void on_sliderSpeed_valueChanged(int value);
	void on_buttonLeft_pressed();
	void on_buttonLeft_released();
	void on_buttonUp_pressed();
	void on_buttonUp_released();
	void on_buttonRight_pressed();
	void on_buttonRight_released();
	void on_buttonDown_pressed();
	void on_buttonDown_released();
	void on_buttonZup_pressed();
	void on_buttonZup_released();
	void on_buttonZdown_pressed();
	void on_buttonZdown_released();
	void on_buttonUup_pressed();
	void on_buttonUup_released();
	void on_buttonUdown_pressed();
	void on_buttonUdown_released();

	void on_buttonGotoX_clicked();
	void on_buttonGotoY_clicked();
	void on_buttonGotoZ_clicked();
	void on_buttonGotoU_clicked();

	void on_buttonHome_clicked();
	void on_buttonStop_clicked();

	void on_actionHomeX2_triggered();

	void slotTimeout();
protected:
	virtual void keyPressEvent( QKeyEvent *event );
	virtual void keyReleaseEvent( QKeyEvent *event );
	virtual void closeEvent(QCloseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
private:
	QStringList speedText;
	Smp86xHandler* smp86xHandler[2];
	int p_id;
};

#endif // PLATFORMCONTROLLER_H
