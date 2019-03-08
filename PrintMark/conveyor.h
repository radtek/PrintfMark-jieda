#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <QWidget>
#include "ui_conveyor.h"

class Conveyor : public QWidget
{
	Q_OBJECT

public:
	Conveyor(Smp86xHandler* sh, Smp86xHandler* sh2, QWidget *parent = 0);
	~Conveyor();

	void setHandler(Smp86xHandler* smp86xHandler){
		this->smp86xHandler = smp86xHandler;
	}

	Ui::Conveyor *ui;
protected slots:
	void on_toolButton_pressed();
	void on_toolButton_2_pressed();
	void on_toolButton_3_pressed();
	void on_toolButton_4_pressed();
	void on_toolButton_5_pressed();
	void on_toolButton_6_pressed();
	void on_toolButton_7_pressed();
	void on_toolButton_8_pressed();
	void on_toolButton_released();
	void on_toolButton_2_released();
	void on_toolButton_3_released();
	void on_toolButton_4_released();
	void on_toolButton_5_released();
	void on_toolButton_6_released();
	void on_toolButton_7_released();
	void on_toolButton_8_released();
 	void on_pushButton_clicked();	// 记录当前X挑宽
// 	void on_pushButton_2_clicked();	// 出板
// 	void on_pushButton_3_clicked();	// 重置
// 	void on_pushButton_4_clicked(); //回原点
	void slotSpeedValueChanged(int value);
private:
	Smp86xHandler* smp86xHandler;
	Smp86xHandler* smp86xHandler2;
};

#endif // CONVEYOR_H