#ifndef TIMERECORD_H
#define TIMERECORD_H

#include <QWidget>
namespace Ui {class TimeRecord;};

class TimeRecord : public QWidget
{
	Q_OBJECT

public:
	TimeRecord(QWidget *parent = 0);
	~TimeRecord();

	void setTime(int index, int msec);
protected:
	virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
	Ui::TimeRecord *ui;
	QTime runTime;
};

#endif // TIMERECORD_H
