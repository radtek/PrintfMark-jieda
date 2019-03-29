#ifndef PRINTMARK_H
#define PRINTMARK_H

#include <QtWidgets/QMainWindow>
#include <QElapsedTimer>
#include <QSerialPort>
#include "ui_printmark.h"

class PlatformController;
class IoMonitor;
class Conveyor;
class SfcWin;
class TimeRecord;

#define offsetFly 3000

struct PROCFLAG
{
	bool real_time;
	bool homing;
	bool conveyor_start;
	bool conveyor_ready;
	bool conveyor_pass;
	bool printing_start;
	bool printing_pause;
	bool scancode_start;
	bool code_empty_err;
	bool cpk_start;
	bool need_beep;
};

struct FLYPRINTF
{
	int enabled;    //使能为1
	int axis;      //0是x，1是y
	int target;    //1实际，2为逻辑
	int mode;      //1+，2-
	int pin;       //选DO口
	int order;     //点数
	long Pos[50];  
};

struct SIGSTAT
{
	int red;
	int alarm;
	int yellow;
	int green;
};

typedef struct _MARK_DATA
{
	QVector3D firstPos;
	QVector3D curntPos;
} MARK_DATA;

class PrintMark : public QMainWindow
{
	Q_OBJECT

public:
	PrintMark(QWidget *parent = 0);
	~PrintMark();

protected slots:
	void on_actionQuit_triggered();
	void on_actionAbout_triggered();
	void on_actionIoPane_triggered();
	void on_actionSysSetup_triggered();
	void on_actionRunParams_triggered();
	void on_actionink_triggered();
	void on_actionCamCalib_triggered();
	void on_actionOffsetSetup_triggered();
	void on_actionNew_triggered();
	void on_actionSave_triggered();
	void on_actionSaveAs_triggered();
	void on_actionLoad_triggered();
/*	void on_actionImport_triggered();*/
	void on_actionRunCpk_triggered();
	void on_actionReadCode_triggered();
	void on_actionGotoCenter_triggered();
	void on_actionTestBadMark_triggered();
	void on_actionSfcWin_triggered();
	void on_actionSfc_triggered(bool checked);
	void on_actionMaintain1_triggered(bool checked);
	void on_actionMaintain2_triggered(bool checked);
	void on_actiondpyBattery_triggered();

	void on_pushButton_clicked();		// 喷码
	void on_pushButton_2_clicked();		// 下一个
	void on_pushButton_3_clicked();		// 读取二维码
	void on_pushButton_4_clicked();		// 开始
	void on_pushButton_5_clicked();		// 停止
	void on_pushButton_6_clicked();		// 传送带
	void on_pushButton_7_clicked();		// 添加
	void on_pushButton_8_clicked();		// 删除
	void on_pushButton_9_clicked();		// 上移
	void on_pushButton_10_clicked();	// 下移
	void on_pushButton_11_clicked();	// 其他
	void on_pushButton_12_clicked(bool checked);	// 管理员
	void on_pushButton_13_clicked(bool checked);	// 直通模式
	void on_pushButton_14_clicked();	// 发送
	void on_pushButton_15_clicked();	// 清除报警
	void on_pushButton_16_clicked();	// 全选
	void on_pushButton_17_clicked();	// 清队列
	void on_pushButton_18_clicked();	// 暂停
	void on_pushButton_22_clicked();				// 时间记录
	void on_pushButton_23_clicked();   //喷码机初始化
	void on_pushButton_24_clicked();   //修改喷码机模板
	void on_pushButton_25_clicked();   //X步进调宽	
	void on_pushButton_26_clicked();

	void drawToAngel();   //为角度而变色
	void on_toolButton_clicked(bool checked);	// 背景灯
	void on_toolButton_2_clicked();				// 基准1
	void on_toolButton_3_clicked();				// 基准2

	void on_checkBox_clicked(bool checked);
	void on_comboBox_currentIndexChanged(int index);
	void on_horizontalSlider_valueChanged(int value);
	void on_checkBox_4_clicked(bool checked);

	void on_tableWidget_customContextMenuRequested(const QPoint & pos);
	void on_tableWidget_2_customContextMenuRequested(const QPoint & pos);
	void on_tableWidget_3_customContextMenuRequested(const QPoint & pos);
	void on_tableWidget_cellChanged(int row, int column);
	void on_tableWidget_2_cellChanged(int row, int column);
	void on_tableWidget_3_cellChanged(int row, int column);
	void on_lineEdit_editingFinished();

	void slotMSettings();
	void slotHomeQuestion();
	
	void slotProcMcu();
	void slotReset();
	void slotTimeout();
	void slotRenewCode();
	void slotCheckExpire();
	void addMessage(const QString& msg, QColor color = Qt::black);
	void updateStatistics();
protected:
	QString timrChange(int num,QString text,QByteArray &code);
	virtual void closeEvent(QCloseEvent *event);
	virtual void mouseDoubleClickEvent( QMouseEvent *event );
	bool doSaveProject(const QString& fileName);
	bool doLoadProject(const QString& fileName);
	void runConveyor(SMP86X_STATUS ss[]);
	void runHoming(SMP86X_STATUS ss[]);
	void runPrinting(SMP86X_STATUS ss[]);
	void runScanCode(SMP86X_STATUS ss[]);
	void checkError(SMP86X_STATUS ss[]);
	void runCpk(SMP86X_STATUS ss[]);
	void runSignal(SMP86X_STATUS ss[]);
	bool visionPos( float& x, float& y, float& u, int m );
	bool visionValid();

	bool printfCurText();
	void printfmove();

	bool writeBadMark( QString filename = QString());
	bool SaveTestData(const QString& strData);
private:
	Ui::PrintMarkClass* ui;

	Smp86xHandler* smp86xHandler[4];
	QLabel* labelCom[4];
	QIODevice* device;
	QIODevice* ink_device;

	QTcpSocket* tcpSocket;
	QLabel* labelTcp;

	PlatformController* platform;
	IoMonitor* ioMonitor[2];
	QTabWidget* tabWidget;
	Conveyor* conveyor;
	SfcWin* sfcWin;
	TimeRecord* timeRecord;
	PRINTINFO printInfo;

	MARK_DATA markData[2];
	PROCFLAG procFlag;
	FLYPRINTF flyprintf;
	SIGSTAT sigStat;
	QString mkucode, mkucode1;
	QString strEmployee;
	QString inkData[8];
	QLabel* labelElapsed;

	int inteval;
	bool closeDown;
	int startPu, clearPu, pausePu, conveyorPass;
	bool sendpre,sendpre2,inkbool,inkbool2;
	int count;
	int waitForUpChain, waitForDownChain;
	int inknum[5];
	int curPrintf = 0;
	QFuture<bool> future;
	
};


class MyItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	MyItemDelegate(QObject* parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
#endif // PRINTMARK_H
