#include "StdAfx.h"
#include "smp86xhandler.h"
#include "smp86xlib.h"

#pragma comment(lib, "smp86xlib")

#pragma region "Smp86xHandler"
#define SMP86X_HOME_FLAG	0x100
#define GOTO_ADDRESS		0x10
#define EMG_INPUT			9
//////////////////////////////////////////////////////////////////////////
void doQuitThread(QThread* thread)
{
	thread->quit();
	thread->wait();
}

Smp86xHandler::Smp86xHandler(const QString& comport, int slave)
	: QObject(0)
	, _slave(slave)
	, emgstop(false)
{
	count = 100;
	memset(&smp86x_status, 0, sizeof(SMP86X_STATUS));
	_thread = QSharedPointer<QThread>(new QThread, &doQuitThread);
	moveToThread(_thread.data());
	QObject::connect(_thread.data(), &QThread::finished, _thread.data(), &QThread::deleteLater);
	QObject::connect(_thread.data(), &QThread::started, this, &Smp86xHandler::sync_smp86x_status);
	_smp86x = QSharedPointer<Smp86x>(Smp86x::create(comport.toLatin1(), 9600));
	_thread->start(QThread::TimeCriticalPriority);
}

Smp86xHandler::Smp86xHandler(const QString& host, const QString& port, int slave)
	: QObject(0)
	, _slave(slave)
	, emgstop(false)
{
	count = 100;
	memset(&smp86x_status, 0, sizeof(SMP86X_STATUS));
	_thread = QSharedPointer<QThread>(new QThread, &doQuitThread);
	moveToThread(_thread.data());
	QObject::connect(_thread.data(), &QThread::finished, _thread.data(), &QThread::deleteLater);
	QObject::connect(_thread.data(), &QThread::started, this, &Smp86xHandler::sync_smp86x_status);
	_smp86x = QSharedPointer<Smp86x>(Smp86x::create(host.toLatin1().constData(), port.toLatin1().constData()));
	_thread->start(QThread::TimeCriticalPriority);
}

Smp86xHandler::Smp86xHandler(const Smp86xHandler& smp86xHandler, int slave)
	: QObject(0)
	, _thread(smp86xHandler._thread)
	, _smp86x(smp86xHandler._smp86x)
	, _slave(slave)
	, emgstop(false)
{
	moveToThread(_thread.data());
	memset(&smp86x_status, 0, sizeof(SMP86X_STATUS));
	count = 100;
}

Smp86xHandler::~Smp86xHandler()
{
	_thread.clear();
	_smp86x.clear();
}

bool Smp86xHandler::isOpen() const
{
	return _smp86x->isOpen();
}

void Smp86xHandler::_setOutput(int slave, int port, int value)
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->setOutput(slave, port, value);
}

void Smp86xHandler::_hitHeader( int slave, int header, int delay )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	//_smp86x->hitHeader(slave, header, delay);
}

void Smp86xHandler::_stop( int slave, int axis )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->stop(slave, axis);
}

void Smp86xHandler::_stopAll( int slave )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->stopAll(slave);
}

void Smp86xHandler::_start(int slave, int axis, int dist, int svel, int cvel, double acc)
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->start(slave, axis, dist, svel, cvel, acc);
}

void Smp86xHandler::_start( int slave, int axis, int svel, int cvel, double acc )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->start(slave, axis, svel, cvel, acc);
}

void Smp86xHandler::_start( int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->start(slave, axis1, axis2, dist1, dist2, svel, cvel, acc);
}

void Smp86xHandler::_start( int slave, int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel, int cvel, double acc )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->start(slave, axis1, axis2, axis3, dist1, dist2, dist3, svel, cvel, acc);
}

void Smp86xHandler::_setPWM( int slave, int port, int value )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->setPWM(slave, port, value);
}

int Smp86xHandler::_writeRawData( int slave, int addr, int nb, ushort* data )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	int ret = _smp86x->writeRawData( slave, addr, nb, data );
	return ret;
}

void Smp86xHandler::_home( int slave, int axis )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	_smp86x->home(slave, axis);
}

void Smp86xHandler::_gotoPos( int slave, int x, int y, int p )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	long data[3] = {0,};
	data[0] = x; data[1] = y;
	data[2] = p ? 2 : 1;
	_smp86x->writeRawData(slave, GOTO_ADDRESS, 5, (ushort*)data);
	//_smp86x->writeRawData(slave, START_ADDRESS, 1, (ushort*)&((const short&)3));
}

int Smp86xHandler::_writeRawBit( int slave, int addr, int state )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(40);
	//	_smp86x->_lastSlave = slave;
	//}
	int ret = _smp86x->writeRawBit( slave, addr, state );
	return ret;
}

int Smp86xHandler::_readRawData( int slave, int addr, int nb, ushort* data )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	int ret = _smp86x->readRawData( slave, addr, nb, data );
	return ret;
}

int Smp86xHandler::_readRawBits( int slave, int addr, int nb, uchar* bits )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = slave;
	//}
	int ret = _smp86x->readRawBits( slave, addr, nb, bits );
	return ret;
}

int Smp86xHandler::_writeRawBits( int slave, int addr, int nb, const uchar* data )
{
	//if (_smp86x->_lastSlave != slave)
	//{
	//	::Sleep(40);
	//	_smp86x->_lastSlave = slave;
	//}
	int ret = _smp86x->writeRawBits( slave, addr, nb, data );
	return ret;
}

void Smp86xHandler::sync_smp86x_status()
{
	//if (_smp86x->_lastSlave != _slave)
	//{
	//	::Sleep(20);
	//	_smp86x->_lastSlave = _slave;
	//}

	SMP86X_STATUS ss = smp86x_status;
	//while(!bQuit)
	{
		int block_size = sizeof(SMP86X_STATUS)/sizeof(short);
		int address = SMP86X_STATUS_ADDRESS;
		int slice_size = 0x50;
		int count = ceil(1.0*block_size/slice_size);

		for (int j=0; j<4; j++)
		{
			ss.axis_status[j].state = 0x0080;
		}
		 
		bool succeeded = true;
		for (int i=0; i<count; i++)
		{
			address = SMP86X_STATUS_ADDRESS + i*slice_size;
			if (-1 == _smp86x->readRawData(_slave, address, qMin(block_size, slice_size), ((ushort*)&ss) + (i*slice_size)))
				{succeeded = false; break;}
			block_size -= slice_size;
		}

		memcpy(&smp86x_status, &ss, sizeof(SMP86X_STATUS));
		//mutex_smp86x.lock();
		succeeded ? wait_smp86x.wakeAll() : NULL;
		//mutex_smp86x.unlock();
	}

	if(count > 30)
	{
		int ret = _smp86x->readRawBits(_slave, SMP86X_HOME_FLAG, 1, &count);
		if (ret != -1 && count == 0)
		{
			_smp86x->writeRawBit(_slave, SMP86X_HOME_FLAG, 1);
			emit homeQuestion();
		}
	} 
	count++;

	if(true)
	{
		//static bool emgstop = ((ss.inputs>>EMG_INPUT) & 0x1);
		if(!((ss.inputs>>EMG_INPUT) & 0x01) && emgstop)
			_smp86x->writeRawBit(_slave, SMP86X_HOME_FLAG, 0);
		emgstop = ((ss.inputs>>EMG_INPUT) & 0x1);
	}

	QTimer::singleShot(5, Qt::PreciseTimer, this, SLOT(sync_smp86x_status()));
}

void Smp86xHandler::quit()
{
	QApplication::removePostedEvents(this);
	deleteLater();
}

#pragma endregion

