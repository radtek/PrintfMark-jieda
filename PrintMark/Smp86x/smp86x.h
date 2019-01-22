#pragma once

//#define HOME_ADDRESS 0x30
#define HOME_ADDRESS 0x28

#pragma pack(push)
#pragma pack(2)
typedef struct _MOVE
{
	unsigned short type;
	unsigned short axis[4];
	long dist[4];
	unsigned short sv;
	unsigned short v;
	unsigned short a;
	unsigned short k;
	unsigned short l;
	unsigned short d;
	unsigned short cmd;
	unsigned short axes;    //WR5
}MOVE;
#pragma pack(pop)

typedef struct _modbus modbus_t;

class Smp86x : public QObject
{
	Q_OBJECT
public:
	Smp86x(const QString& comport, int timeout = 500){
		m_modbus = NULL;
		offsetX = 0;
		offsetY = 0;
		_opened = initializeDevice(comport, timeout);

		QThread* thread = new QThread;
		moveToThread(thread);
		QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
		//QObject::connect(thread, &QThread::finished, this, &Smp86x::deleteLater, Qt::DirectConnection);
	}
	Smp86x(const char* comport, int timeout = 500){
		m_modbus = NULL;
		offsetX = 0;
		offsetY = 0;
		_opened = initializeDevice(QString(comport), timeout);

		QThread* thread = new QThread;
		moveToThread(thread);
		QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
		//QObject::connect(thread, &QThread::finished, this, &Smp86x::deleteLater, Qt::DirectConnection);
	}
	Smp86x(const QString& host, const QString& port, int timeout = 500)
	{
		m_modbus = NULL;
		offsetX = 0;
		offsetY = 0;
		_opened = initializeDevice(host, port, timeout);

		QThread* thread = new QThread;
		moveToThread(thread);
		QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
	}
	~Smp86x()
	{
		uninitializeDevide();
	}
	enum
	{
		READY = 0,
		RUNNING = 0x0F,
		DRVERR = 0xF0,
	};

	modbus_t* modbus() const{return m_modbus;}

	bool isOpened() const {return _opened;}
	bool initializeDevice(const QString& comport, int timeout);
	bool initializeDevice(const QString& host, const QString& port, int timeout);
	void uninitializeDevide();
	void home(int slave, int axis);
	void setLogicalLimit(int slave, int axis, int select, int limit);
	void setMagnification(int vel);
	void setLimitEnabled(int slave, int axis, bool enable);

	void stop(int slave, int axis);
	void stopAll(int slave = 0xa);
	void getLastState(int slave, int* state);

	void getCounter(int slave, int axis, int* pos, int* ppos = NULL);
	void setCounter(int slave, int axis, int pos);
	void setOffsetXY(int x, int y);

	void start(int slave, int axis, int dist, int svel, int cvel, double acc);
	void start(int slave, int axis, int svel, int cvel, double acc);
	void start(int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc);
	void start(int slave, int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel, int cvel, double acc);
	void changeSpeed(int slave, int axis, int vel);

	void setServo(int slave, int port, bool enable);
	void getStatus(int slave, ulong* status);
	void setPWM(int slave, int port, int value);
	void setOutput(int slave, int port, int value);
	void getOutputs(int slave, ushort* value);
	void getInput(int slave, int port, int* value);
	void getInputs(int slave, ushort* value);
	void hitHeader( int slave, int header, int delay );

	//__declspec(dllimport) bool isIOEnabled( int port);

	void setBeep(bool on);

	int writeRawData(int slave, int addr, int nb, ushort* data);
	int readRawData(int slave, int addr, int nb, ushort* data);
	int writeRawBit(int slave, int addr, int state);
	int writeRawBits(int slave, int addr, int nb, const uchar* data);
	int readRawBits(int slave, int addr, int nb, uchar* bits);

	int _lastSlave;
private:
	modbus_t* m_modbus;
	QMutex mutex;
	//bool bTimeout = false;
	//QTime time;
	int offsetX;
	int offsetY;
	bool _opened;
};