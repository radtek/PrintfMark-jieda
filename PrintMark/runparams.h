#ifndef RUNPARAMS_H
#define RUNPARAMS_H

#include <QWidget>
namespace Ui {class RunParams;};


class RunParams : public QWidget
{
	Q_OBJECT

public:
	RunParams(Smp86xHandler* sh, QWidget *parent = 0);
	~RunParams();

	void setHandler(Smp86xHandler* smp86xHandler){
		this->smp86xHandler = smp86xHandler;
	}

	Q_SIGNAL void paramsChanged();
protected slots:
	void on_buttonBox_clicked(QAbstractButton * button);
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_toolButton_clicked();
	void on_toolButton_2_clicked();
	void on_lineEdit_14_textEdited(const QString &text);
	void on_lineEdit_17_textEdited(const QString &text);

protected:
	virtual void mouseDoubleClickEvent( QMouseEvent *event );
private:
	Ui::RunParams *ui;
	Smp86xHandler* smp86xHandler;
};

#endif // RUNPARAMS_H
