#ifndef SMP86XHANDLER_H
#define SMP86XHANDLER_H

#include <QObject>

#define SMP86X_STATUS_ADDRESS	0x20
#pragma pack(push)
#pragma pack(2)
struct AXIS_STATUS
{
	long logicPos;
	long realPos;
	unsigned short state; //高8位:[EMG/ALM/EL-/EL+/IN3/IN2/IN1/IN0]低8位:[/////RESERVE/ERR/DRV]
};

struct SMP86X_STATUS	//最大空间96字节
{
	AXIS_STATUS axis_status[4];	//各轴状态
	ulong inputs;				//DI状态
	ulong outputs;				//DO状态
};
#pragma pack(pop)

class Smp86x;

class Smp86xHandler : public QObject
{
	Q_OBJECT

public:
	Smp86xHandler(const QString& comport, int slave);
	Smp86xHandler(const QString& host, const QString& port, int slave);
	Smp86xHandler(const Smp86xHandler& smp86xHandler, int slave);
	void quit();

	bool isOpen() const;

	void setOutput(int port, int value)
	{
		QMetaObject::invokeMethod(this, "_setOutput", Q_ARG(int, _slave), Q_ARG(int, port), Q_ARG(int, value));
	}
	void hitHeader(int header, int delay)
	{
		QMetaObject::invokeMethod(this, "_hitHeader", Q_ARG(int, _slave), Q_ARG(int, header), Q_ARG(int, delay));
	}
	void stop(int axis)
	{
		writeRawBit(0x50, 1);
		QMetaObject::invokeMethod(this, "_stop", Q_ARG(int, _slave), Q_ARG(int, axis));
	}
	void stopAll()
	{
		writeRawBit(0x50, 1);
		QMetaObject::invokeMethod(this, "_stopAll", Q_ARG(int, _slave));
	}
	void start(int axis, int dist, int svel=-1, int cvel=-1, double acc=0.0)
	{
		QMetaObject::invokeMethod(this, "_start", Q_ARG(int, _slave), Q_ARG(int, axis), Q_ARG(int, dist), Q_ARG(int, svel), Q_ARG(int, cvel), Q_ARG(double, acc));
	}
	void start(int axis, int svel=-1, int cvel=-1, double acc=0.0)
	{
		QMetaObject::invokeMethod(this, "_start", Q_ARG(int, _slave), Q_ARG(int, axis), Q_ARG(int, svel), Q_ARG(int, cvel), Q_ARG(double, acc));
	}
	void start(int axis1, int axis2, int dist1, int dist2, int svel=-1, int cvel=-1, double acc=0.0)
	{
		QMetaObject::invokeMethod(this, "_start", Q_ARG(int, _slave), Q_ARG(int, axis1), Q_ARG(int, axis2), Q_ARG(int, dist1), Q_ARG(int, dist2), Q_ARG(int, svel), Q_ARG(int, cvel), Q_ARG(double, acc));
	}
	void start(int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel=-1, int cvel=-1, double acc=0.0)
	{
		QMetaObject::invokeMethod(this, "_start", Q_ARG(int, _slave), Q_ARG(int, axis1), Q_ARG(int, axis2), Q_ARG(int, axis3), Q_ARG(int, dist1), Q_ARG(int, dist2), Q_ARG(int, dist3), Q_ARG(int, svel), Q_ARG(int, cvel), Q_ARG(double, acc));
	}
	void gotoPos(int x, int y, int p)
	{
		QMetaObject::invokeMethod(this, "_gotoPos", Q_ARG(int, _slave), Q_ARG(int, x), Q_ARG(int, y), Q_ARG(int, p));
	}
	void home(int axis)
	{
		QMetaObject::invokeMethod(this, "_home", Q_ARG(int, _slave), Q_ARG(int, axis));
	}
	void setPWM(int port, int value)
	{
		QMetaObject::invokeMethod(this, "_setPWM", Q_ARG(int, _slave), Q_ARG(int, port), Q_ARG(int, value));
	}
	int writeRawData(int addr, int nb, ushort* data)
	{
		int ret = -1;
		QMetaObject::invokeMethod(this, "_writeRawData", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, ret), Q_ARG(int, _slave), Q_ARG(int, addr), Q_ARG(int, nb), Q_ARG(ushort*, data));
		return ret;
	}
	int writeRawBit(int addr, int state)
	{
		int ret = -1;
		QMetaObject::invokeMethod(this, "_writeRawBit", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, ret), Q_ARG(int, _slave), Q_ARG(int, addr), Q_ARG(int, state));
		return ret;
	}
	int writeRawBits(int addr, int nb, const uchar* data)
	{
		int ret = -1;
		QMetaObject::invokeMethod(this, "_writeRawBits", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, ret), Q_ARG(int, _slave), Q_ARG(int, addr), Q_ARG(int, nb), Q_ARG(const uchar*, data));
		return ret;
	}
	int readRawData(int addr, int nb, ushort* data)
	{
		int ret = -1;
		QMetaObject::invokeMethod(this, "_readRawData", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, ret), Q_ARG(int, _slave), Q_ARG(int, addr), Q_ARG(int, nb), Q_ARG(ushort*, data));
		return ret;
	}
	int readRawBits(int addr, int nb, uchar* bits)
	{
		int ret = -1;
		QMetaObject::invokeMethod(this, "_readRawBits", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, ret), Q_ARG(int, _slave), Q_ARG(int, addr), Q_ARG(int, nb), Q_ARG(uchar*, bits));
		return ret;
	}

	SMP86X_STATUS getSmp86xStatus(bool rt = false) const
	{
		SMP86X_STATUS ss;
		memset(&ss, 0, sizeof(ss));

		if(rt)
		{
			mutex_smp86x.lock();
			wait_smp86x.wait(&mutex_smp86x, 3000);
			memcpy(&ss, &smp86x_status, sizeof(ss));
			mutex_smp86x.unlock();
		}
		else
		{
			memcpy(&ss, &smp86x_status, sizeof(ss));
		}

		return ss;
	}
	Q_SIGNAL void homeQuestion();
protected slots:
	void _setOutput(int slave, int port, int value);
	void _hitHeader(int slave, int header, int delay);
	void _stop(int slave, int axis);
	void _stopAll(int slave);
	void _start(int slave, int axis, int dist, int svel, int cvel, double acc);
	void _start(int slave, int axis, int svel, int cvel, double acc);
	void _start(int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc);
	void _start(int slave, int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel, int cvel, double acc);
	void _gotoPos(int slave, int x, int y, int p);
	void _home(int slave, int axis);
	void _setPWM(int slave, int port, int value);
	int _writeRawData(int slave, int addr, int nb, ushort* data);
	int _readRawData(int slave, int addr, int nb, ushort* data);
	int _writeRawBit(int slave, int addr, int state);
	int _writeRawBits(int slave, int addr, int nb, const uchar* data);
	int _readRawBits(int slave, int addr, int nb, uchar* bits);
	void sync_smp86x_status();

protected:
	~Smp86xHandler();
private:
	QSharedPointer<Smp86x> _smp86x;
	QSharedPointer<QThread> _thread;
	int _slave;
	mutable QMutex mutex_smp86x;
	mutable QWaitCondition wait_smp86x;
	SMP86X_STATUS smp86x_status;
	uchar count;
	bool emgstop;
};

#endif // SMP86XHANDLER_H
