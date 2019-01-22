#include "stdafx.h"
#include "smp86x.h"
#include "modbus.h"

//#define _err_out(a, b)  {char buff[1024];sprintf(buff, a, b);OutputDebugStringA(buff);}
#define _err_out(a, b)  {}

#define modbus_write_register	([](modbus_t *ctx, int reg_addr, int value)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	  if((x=modbus_write_register(ctx, reg_addr, value)) == -1) \
          _err_out("modbus_write_register fail %d\n", mb_ec++)\
	return x;})
#define modbus_write_registers	([](modbus_t *ctx, int reg_addr, int nb, const uint16_t *data)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	if((x=modbus_write_registers(ctx, reg_addr, nb, data)) == -1) \
          _err_out("modbus_write_registers fail %d\n", mb_ec++)\
	return x;})
#define modbus_read_registers	([](modbus_t *ctx, int addr, int nb, uint16_t *dest)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	if((x=modbus_read_registers(ctx, addr, nb, dest)) == -1)\
          _err_out("modbus_read_registers fail %d\n", mb_ec++)\
	return x;})
#define modbus_write_bit		([](modbus_t *ctx, int coil_addr, int state)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	if((x=modbus_write_bit(ctx, coil_addr, state)) == -1)\
          _err_out("modbus_write_bit fail %d\n", mb_ec++)\
	return x;})
#define modbus_write_bits		([](modbus_t *ctx, int addr, int nb, const uint8_t *data)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	if((x=modbus_write_bits(ctx, addr, nb, data)) == -1)\
          _err_out("modbus_write_bits fail %d\n", mb_ec++)\
	return x;})
#define modbus_read_bits		([](modbus_t *ctx, int addr, int nb, uint8_t *dest)->int{\
	/*QMutexLocker l(&_mutex);*/\
	int x=-1;\
	for(int i=0; i<3&&x==-1; i++)\
	if((x=modbus_read_bits(ctx, addr, nb, dest)) == -1)\
          _err_out("modbus_read_bits fail %d\n", mb_ec++)\
	return x;})

const long RAN = 8e6/50;
//static QMutex _mutex;
//namespace Smp86x
//{
	//__declspec(dllexport) void start( int axis, int dist, int svel, int cvel, double acc );
	//__declspec(dllexport) void start(int axis, int svel, int cvel, double acc);

int mb_ec = 0;


	//////////////////////////////////////////////////////////////////////////
	bool Smp86x::initializeDevice(const QString& comport, int timeout)
	{
		int ret = -1;
		QMutexLocker l(&mutex);
		if( m_modbus )
		{
			modbus_close( m_modbus );
			modbus_free( m_modbus );
			m_modbus = NULL;
		}

		m_modbus = modbus_new_rtu( comport.toLatin1().constData(), 115200, 'N', 1, 1);
		if((ret = modbus_connect( m_modbus )) == -1)
		{
			modbus_close( m_modbus );
			modbus_free( m_modbus );
			m_modbus = NULL;
			return false;
		}

		static timeval tv = { timeout / 1000, (timeout % 1000) * 1000 };
		modbus_set_timeout_begin(m_modbus, &tv);
		modbus_set_timeout_end(m_modbus, &tv);
		return (ret != -1);
	}

	bool Smp86x::initializeDevice(const QString& host, const QString& port, int timeout)
	{
		int ret = -1;
		QMutexLocker l(&mutex);
		if( m_modbus )
		{
			modbus_close( m_modbus );
			modbus_free( m_modbus );
			m_modbus = NULL;
		}

		m_modbus = modbus_new_tcp( host.toLatin1(), port.toInt());
		modbus_set_error_recovery(m_modbus, 1);
		modbus_set_debug(m_modbus, 1);
		if((ret = modbus_connect( m_modbus )) == -1)
		{
			modbus_close( m_modbus );
			modbus_free( m_modbus );
			m_modbus = NULL;
			return false;
		}

		static timeval tv = { timeout / 1000, (timeout % 1000) * 1000 };
		modbus_set_timeout_begin(m_modbus, &tv);
		modbus_set_timeout_end(m_modbus, &tv);
		return (ret != -1);
	}

	//bool Smp86x::initializeDevice( void* modbus )
	//{
	//	QMutexLocker l(&mutex);
	//	if( m_modbus )
	//	{
	//		modbus_close( m_modbus );
	//		modbus_free( m_modbus );
	//	}
	//	m_modbus = static_cast<modbus_t*>(modbus);

	//	return (m_modbus != nullptr);
	//}

	//void* Smp86x::getDevice()
	//{
	//	return m_modbus;
	//}

	void Smp86x::uninitializeDevide()
	{
		QMutexLocker l(&mutex);
		modbus_close( m_modbus );
		modbus_free( m_modbus );
		m_modbus = NULL;
		_opened = false;
	}

	void Smp86x::home(int slave, int axis)
	{

		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;
		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_bit(m_modbus, HOME_ADDRESS+axis, 1);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}
		
		//modbus_write_bit(m_modbus, HOME_ADDRESS+axis, 0);
	}

	void Smp86x::setPWM( int slave, int port, int value )
	{
		if( !m_modbus )
			return;

		//if (bTimeout && time.elapsed() < 50)
		//	return;

		QMutexLocker l(&mutex);
		//bTimeout = false;
		modbus_set_slave( m_modbus, slave );
		int ret = modbus_write_register(m_modbus, port+8, value);
		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}
	}

	void Smp86x::setLogicalLimit(int slave, int axis, int select, int limit)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		//bTimeout = false;
		modbus_set_slave( m_modbus, slave );
		int ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&limit);
		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		switch(axis)
		{
		case 0:
			modbus_write_register(m_modbus, 0, ((select == 0) ? 0x0c : 0x0b)|0x0100);	// 1轴
			break;
		case 1:
			modbus_write_register(m_modbus, 0, ((select == 0) ? 0x0c : 0x0b)|0x0200);	// 2轴
			break;
		case 2:
			modbus_write_register(m_modbus, 0, ((select == 0) ? 0x0c : 0x0b)|0x0400);	// 3轴
			break;
		case 3:
			modbus_write_register(m_modbus, 0, ((select == 0) ? 0x0c : 0x0b)|0x0800);	// 4轴
			break;
		default:
			return;
		}

	}

	void Smp86x::setLimitEnabled(int slave, int axis, bool enable)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		//bTimeout = false;
		int ret = -1;

		ushort d = 0;
		switch(axis)
		{
		case 0:
			d = (0x0f|0x0100);	// 1轴
			//modbus_write_register(m_modbus, 1, (enable ? 0x1e00 : 0));
			break;
		case 1:
			d = (0x0f|0x0200);	// 2轴
			break;
		case 2:
			d = (0x0f|0x0400);	// 3轴
			break;
		case 3:
			d = (0x0f|0x0800);	// 4轴
			break;
		default:
			return;
		}

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0, 1, (ushort*)&d);
		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}
		d = (enable ? 0x3 : 0);
		ret = modbus_write_registers(m_modbus, 2, 1, (ushort*)&d);
	}

	void Smp86x::setMagnification(int vel)
	{
		*const_cast<long*>(&RAN) = 8e6/vel;
	}

	void Smp86x::stop( int slave, int axis )
	{
		int ret = -1;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		switch(axis)
		{
		case 0:
			ret = modbus_write_register(m_modbus, 0,0x26|0x0100);	//1轴减速停止
			break;
		case 1:
			ret = modbus_write_register(m_modbus, 0,0x26|0x0200);	//2轴减速停止
			break;
		case 2:
			ret = modbus_write_register(m_modbus, 0,0x26|0x0400);	//3轴减速停止
			break;
		case 3:
			ret = modbus_write_register(m_modbus, 0,0x26|0x0800);	//4轴减速停止
			break;
		default:
			break;
		}

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}
	}

	void Smp86x::stopAll(int slave)
	{
		int ret = -1;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_register(m_modbus, 0,0x27|0x0F00);	//4轴减速停止

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}
	}

	void Smp86x::getLastState(int slave, int* state)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//{
		//	*state = -1;
		//	return;
		//}

		int ret = -1;
		ushort r = 0;

		QMutexLocker l(&mutex);
		if( !m_modbus )
		{
			*state = -1;
			return;
		}

		modbus_set_slave( m_modbus, slave );
		ret = modbus_read_registers(m_modbus, 0, 1, &r);	//RR0

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			*state = -1;
			return;
		}

		*state = (r&0xFF);
		//*state = bool(r&0xF);		//RR0 bit 0~3
	}

	void Smp86x::getCounter( int slave, int axis, int* pos, int* ppos)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		switch(axis)
		{
		case 0:
			ret = modbus_write_register(m_modbus, 0, 0x10|0x0100);	//1轴
			break;
		case 1:
			ret = modbus_write_register(m_modbus, 0, 0x10|0x0200);	//2轴
			break;
		case 2:
			ret = modbus_write_register(m_modbus, 0, 0x10|0x0400);	//3轴
			break;
		case 3:
			ret = modbus_write_register(m_modbus, 0, 0x10|0x0800);	//4轴
			break;
		default:
			return;
		}

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		modbus_read_registers( m_modbus, 6, 2, (ushort*)pos );
		if(axis == 0) *pos -= offsetX;
		if(axis == 1) *pos -= offsetY;
		//modbus_read_registers( m_modbus, 7, 1, &((ushort*)pos)[1] );

		if(ppos) 
		{
			switch(axis)
			{
			case 0:
				ret = modbus_write_register(m_modbus, 0, 0x11|0x0100);	//1轴
				break;
			case 1:
				ret = modbus_write_register(m_modbus, 0, 0x11|0x0200);	//2轴
				break;
			case 2:
				ret = modbus_write_register(m_modbus, 0, 0x11|0x0400);	//3轴
				break;
			case 3:
				ret = modbus_write_register(m_modbus, 0, 0x11|0x0800);	//4轴
				break;
			default:
				return;
			}

			if (ret == -1)
			{
				//bTimeout = true;
				//time.restart();
				return;
			}
			modbus_read_registers( m_modbus, 6, 2, (ushort*)ppos );
			//modbus_read_registers( m_modbus, 7, 1, &((ushort*)pos)[1] );
		}
	}

	void Smp86x::setCounter( int slave, int axis, int pos )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&pos);	//低位数据设置
		//modbus_write_register(m_modbus, 7, pos>>16);	//高位数据设置

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		switch(axis)
		{
		case 0:
			modbus_write_register(m_modbus, 0, 0x09|0x0100);	//1轴
			break;
		case 1:
			modbus_write_register(m_modbus, 0, 0x09|0x0200);	//2轴
			break;
		case 2:
			modbus_write_register(m_modbus, 0, 0x09|0x0400);	//3轴
			break;
		case 3:
			modbus_write_register(m_modbus, 0, 0x09|0x0800);	//4轴
			break;
		default:
			break;
		}
	}

	void Smp86x::setOffsetXY(int x, int y)
	{
		offsetX = x;
		offsetY = y;
	}

	void Smp86x::getStatus( int slave, ulong* status )
	{

		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;

		ulong s = 0;
		ushort axis[] = {0x0100, 0x0200, 0x0400, 0x0800};

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;
		modbus_set_slave( m_modbus, slave );
		ret =modbus_read_registers( m_modbus, 4, 2, (ushort*)status);
		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		for (int i=0; i<4; i++)
		{
			ret = modbus_write_register(m_modbus, 0, 0x0f|axis[i]);
			ret = modbus_read_registers(m_modbus, 2, 2, (ushort*)&s);
			(s & 0x08) ? *status |= ((0x20) << (8*i)) : *status &= ~((0x20) << (8*i));
			(s & 0x04) ? *status |= ((0x10) << (8*i)) : *status &= ~((0x10) << (8*i));
			(s & 0x10) ? *status |= ((0x80) << (8*i)) : *status &= ~((0x80) << (8*i));
			(s & 0x20) ? *status |= ((0x40) << (8*i)) : *status &= ~((0x40) << (8*i));
		}
	}

	void Smp86x::start( int slave, int axis, int dist, int svel, int cvel, double acc )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;
		MOVE _move;
		memset(&_move, 0, sizeof(MOVE));

		_move.type = 1;
		_move.a = 8000;//qAbs(LONG(((cvel-svel)/acc)/(1e9/RAN)));
		_move.k = qMax(1.0, 6.25e7*(8e6/RAN)/(4.0*(cvel-svel)/(acc*acc)));

		_move.cmd = (dist>0) ? 0x20 : 0x21;

		svel = (svel == -1) ? -1 : qAbs(svel)/(8e6/RAN);
		cvel = (cvel == -1) ? -1 : qAbs(cvel)/(8e6/RAN);
		svel = (svel == -1) ? -1 : qMax<int>(1, svel);
		cvel = (cvel == -1) ? -1 : qMax<int>(1, cvel);
		svel = (svel == -1) ? -1 : qMin<int>(8000, svel);
		cvel = (cvel == -1) ? -1 : qMin<int>(8000, cvel);
		_move.dist[0] = qAbs(dist);
		_move.sv = svel;
		_move.v = cvel;
		_move.axis[0] = (1<<(8+axis))&0xFF00;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0x100, sizeof(MOVE)/2, (ushort*)&_move);
#if 0
		//modbus_write_register(m_modbus, 0, 0xF|x);
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速
		if(svel != -1)
		{
			ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&svel);
			//modbus_write_register(m_modbus, 7,svel>>16);

			if (ret == -1)
			{
				//bTimeout = true;
				//time.restart();
				return;
			}

			modbus_write_register(m_modbus, 0,0x04|x);//初始速度
		}

		if(cvel != -1)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&cvel);
			//modbus_write_register(m_modbus, 7,cvel>>16);
			modbus_write_register(m_modbus, 0,0x05|x);//驱动速度
		}

		if(acc != 0.0)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&lacc);
			//modbus_write_register(m_modbus, 7,lacc>>16);
			modbus_write_register(m_modbus, 0,0x02|x);//加速度

			modbus_write_registers(m_modbus, 6, 2, (ushort*)&jerk);
			//modbus_write_register(m_modbus, 7,jerk>>16);
			modbus_write_register(m_modbus, 0,0x01|x);//加加速度
		}

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist);
		//modbus_write_register(m_modbus, 7,dist>>16);
		modbus_write_register(m_modbus, 0,0x06|x);//输出脉冲数

		modbus_write_register(m_modbus, 0, ldir|x);
#endif // 0
	}

	void Smp86x::start( int slave, int axis, int svel, int cvel, double acc )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;
		MOVE _move;
		memset(&_move, 0, sizeof(MOVE));

		_move.type = 2;
		_move.a = 8000;//qAbs(LONG(((cvel-svel)/acc)/(1e9/RAN)));
		_move.k = qMax(1.0, 6.25e7*(8e6/RAN)/(4.0*(qAbs(cvel)-qAbs(svel))/(acc*acc)));

		_move.cmd = (cvel>0) ? 0x22 : 0x23;

		svel = (svel == -1) ? -1 : qAbs(svel)/(8e6/RAN);
		cvel = (cvel == -1) ? -1 : qAbs(cvel)/(8e6/RAN);
		svel = (svel == -1) ? -1 : qMax<int>(1, svel);
		cvel = (cvel == -1) ? -1 : qMax<int>(1, cvel);
		svel = (svel == -1) ? -1 : qMin<int>(8000, svel);
		cvel = (cvel == -1) ? -1 : qMin<int>(8000, cvel);
		_move.sv = svel;
		_move.v = cvel;
		_move.axis[0] = (1<<(8+axis))&0xFF00;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0x100, sizeof(MOVE)/2, (ushort*)&_move);
#if 0
		//modbus_write_register(m_modbus, 0, 0xF|x);
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速
		if(svel != -1)
		{
			ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&svel);
			//modbus_write_register(m_modbus, 7,svel>>16);

			if (ret == -1)
			{
				//bTimeout = true;
				//time.restart();
				return;
			}

			modbus_write_register(m_modbus, 0,0x04|x);		//初始速度
		}

		if(cvel != -1)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&cvel);
			//modbus_write_register(m_modbus, 7,cvel>>16);
			modbus_write_register(m_modbus, 0,0x05|x);		//驱动速度
		}

		if(acc != 0.0)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&lacc);
			//modbus_write_register(m_modbus, 7,lacc>>16);
			modbus_write_register(m_modbus, 0,0x02|x);//加速度

			modbus_write_registers(m_modbus, 6, 2, (ushort*)&jerk);
			//modbus_write_register(m_modbus, 7,jerk>>16);
			modbus_write_register(m_modbus, 0,0x01|x);//加加速度
		}

		modbus_write_register(m_modbus, 0, dir|x);
#endif // 0
	}

#if 0
	void Smp86x::start_s( int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;

		LONG lacc = qAbs(LONG(((cvel-svel)/acc)/(1e9/RAN)));
		LONG jerk = qMax(1.0, 6.25e7*(8e6/RAN)/(4.0*(cvel-svel)/(acc*acc)));

		ushort ax1 = (1<<(8+axis1))&0xFF00;
		ushort ax2 = (1<<(8+axis2))&0xFF00;
		axis1 = axis1<<0;
		axis2 = axis2<<2;

		/*if(lacc > 8000 || lacc == 0) */lacc = 8000;
		svel = (svel == -1) ? -1 : qAbs(svel)/(8e6/RAN);
		cvel = (cvel == -1) ? -1 : qAbs(cvel)/(8e6/RAN);
		svel = (svel == -1) ? -1 : qMax<int>(1, svel);
		cvel = (cvel == -1) ? -1 : qMax<int>(1, cvel);
		svel = (svel == -1) ? -1 : qMin<int>(8000, svel);
		cvel = (cvel == -1) ? -1 : qMin<int>(8000, cvel);

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		//modbus_write_register(m_modbus, 0, 0xF|ax1|ax2);
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速
		if(svel != -1)
		{
			ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&svel);
			//modbus_write_register(m_modbus, 7,svel>>16);

			if (ret == -1)
			{
				//bTimeout = true;
				//time.restart();
				return;
			}

			modbus_write_register(m_modbus, 0,0x04|ax1);//初始速度
		}

		if(cvel != -1)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&cvel);
			//modbus_write_register(m_modbus, 7,cvel>>16);
			modbus_write_register(m_modbus, 0,0x05|ax1);//驱动速度
		}

		if(acc != 0.0)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&lacc);
			//modbus_write_register(m_modbus, 7,lacc>>16);
			modbus_write_register(m_modbus, 0,0x02|ax1);//加速度

			modbus_write_registers(m_modbus, 6, 2, (ushort*)&jerk);
			//modbus_write_register(m_modbus, 7,jerk>>16);
			modbus_write_register(m_modbus, 0,0x01|ax1);//加加速度
		}

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist1);
		//modbus_write_register(m_modbus, 7,dist1>>16);
		modbus_write_register(m_modbus, 0,0x06|ax1);//输出脉冲数
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist2);
		//modbus_write_register(m_modbus, 7,dist2>>16);
		modbus_write_register(m_modbus, 0,0x06|ax2);//输出脉冲数
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速

		modbus_write_register(m_modbus, 5, axis1|axis2);
		modbus_write_register(m_modbus, 0, 0x3B);
		modbus_write_register(m_modbus, 0, 0x30);
	}
#endif // 0

	void Smp86x::start( int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;
		MOVE _move;
		memset(&_move, 0, sizeof(MOVE));

		_move.type = 3;
		_move.a = 8000;//qAbs(LONG(((cvel-svel)/acc)/(1e9/RAN)));
		_move.k = qMax(1.0, 6.25e7*(8e6/RAN)/(4.0*(cvel-svel)/(acc*acc)));

		_move.axis[0] = (1<<(8+axis1))&0xFF00;
		_move.axis[1] = (1<<(8+axis2))&0xFF00;
		_move.dist[0] = dist1;
		_move.dist[1] = dist2;
		_move.axes = (axis1<<0) | (axis2<<2);

		svel = (svel == -1) ? -1 : qAbs(svel)/(8e6/RAN);
		cvel = (cvel == -1) ? -1 : qAbs(cvel)/(8e6/RAN);
		svel = (svel == -1) ? -1 : qMax<int>(1, svel);
		cvel = (cvel == -1) ? -1 : qMax<int>(1, cvel);
		svel = (svel == -1) ? -1 : qMin<int>(8000, svel);
		cvel = (cvel == -1) ? -1 : qMin<int>(8000, cvel);

		_move.sv = svel;
		_move.v = cvel;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0x100, sizeof(MOVE)/2, (ushort*)&_move);
	}

	void Smp86x::start( int slave, int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel, int cvel, double acc )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;
		MOVE _move;
		memset(&_move, 0, sizeof(MOVE));

		_move.type = 4;
		_move.a = 8000;//qAbs(LONG(((cvel-svel)/acc)/(1e9/RAN)));
		_move.k = qMax(1.0, 6.25e7*(8e6/RAN)/(4.0*(cvel-svel)/(acc*acc)));

		_move.axis[0] = (1<<(8+axis1))&0xFF00;
		_move.axis[1] = (1<<(8+axis2))&0xFF00;
		_move.axis[2] = (1<<(8+axis3))&0xFF00;
		_move.dist[0] = dist1;
		_move.dist[1] = dist2;
		_move.dist[2] = dist3;
		_move.axes = (axis1<<0) | (axis2<<2) | (axis3<<4);

		svel = (svel == -1) ? -1 : qAbs(svel)/(8e6/RAN);
		cvel = (cvel == -1) ? -1 : qAbs(cvel)/(8e6/RAN);
		svel = (svel == -1) ? -1 : qMax<int>(1, svel);
		cvel = (cvel == -1) ? -1 : qMax<int>(1, cvel);
		svel = (svel == -1) ? -1 : qMin<int>(8000, svel);
		cvel = (cvel == -1) ? -1 : qMin<int>(8000, cvel);
		_move.sv = svel;
		_move.v = cvel;

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0x100, sizeof(MOVE)/2, (ushort*)&_move);
#if 0
		//modbus_write_register(m_modbus, 0, 0xF|ax1|ax2|ax3);
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速
		if(svel != -1)
		{
			ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&svel);
			//modbus_write_register(m_modbus, 7,svel>>16);

			if (ret == -1)
			{
				//bTimeout = true;
				//time.restart();
				return;
			}

			modbus_write_register(m_modbus, 0,0x04|ax1);//初始速度
		}

		if(cvel != -1)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&cvel);
			//modbus_write_register(m_modbus, 7,cvel>>16);
			modbus_write_register(m_modbus, 0,0x05|ax1);//驱动速度
		}

		if(acc != 0.0)
		{
			modbus_write_registers(m_modbus, 6, 2, (ushort*)&lacc);
			//modbus_write_register(m_modbus, 7,lacc>>16);
			modbus_write_register(m_modbus, 0,0x02|ax1);//加速度

			modbus_write_registers(m_modbus, 6, 2, (ushort*)&jerk);
			//modbus_write_register(m_modbus, 7,jerk>>16);
			modbus_write_register(m_modbus, 0,0x01|ax1);//加加速度
		}

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist1);
		//modbus_write_register(m_modbus, 7,dist1>>16);
		modbus_write_register(m_modbus, 0,0x06|ax1);//输出脉冲数
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist2);
		//modbus_write_register(m_modbus, 7,dist2>>16);
		modbus_write_register(m_modbus, 0,0x06|ax2);//输出脉冲数
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速

		modbus_write_registers(m_modbus, 6, 2, (ushort*)&dist3);
		//modbus_write_register(m_modbus, 7,dist3>>16);
		modbus_write_register(m_modbus, 0,0x06|ax3);//输出脉冲数
		//modbus_write_register(m_modbus, 3, 0x0004);//S加减速

		modbus_write_register(m_modbus, 5, axis1|axis2|axis3);
		modbus_write_register(m_modbus, 0, 0x3B);
		modbus_write_register(m_modbus, 0, 0x31);
#endif // 0
	}

	void Smp86x::changeSpeed( int slave, int axis, int vel )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = -1;
		//bTimeout = false;

		vel = qAbs(vel)/(8e6/RAN);
		vel = qMax<int>(1, vel);
		vel = qMin<int>(8000, vel);

		QMutexLocker l(&mutex);
		if( !m_modbus )
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 6, 2, (ushort*)&vel);
		//modbus_write_register(m_modbus, 7,vel>>16);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		switch(axis)
		{
		case 0:
			modbus_write_register(m_modbus, 0,0x05|0x0100);	//1轴
			break;
		case 1:
			modbus_write_register(m_modbus, 0,0x05|0x0200);	//2轴
			break;
		case 2:
			modbus_write_register(m_modbus, 0,0x05|0x0400);	//3轴
			break;
		case 3:
			modbus_write_register(m_modbus, 0,0x05|0x0800);	//4轴
			break;
		default:
			break;
		}
	}

	int Smp86x::writeRawData( int slave, int addr, int nb, ushort* data )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return -1;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return -1;

		modbus_set_slave( m_modbus, slave );
		const int slice = 0x50;
		for(int i=0; i<ceilf(nb*1.0/slice); i++)
		{
			ret = modbus_write_registers(m_modbus, addr+slice*i, qMin(slice, nb-slice*i), data+slice*i);
			if(ret == -1)
				break;
		}

		return ret;
	}

	int Smp86x::readRawData( int slave, int addr, int nb, ushort* data )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return -1;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return -1;

		modbus_set_slave( m_modbus, slave );
		const int slice = 0x50;
		for(int i=0; i<ceilf(nb*1.0/slice); i++)
		{
			ret = modbus_read_registers(m_modbus, addr+slice*i, qMin(slice, nb-slice*i), data+slice*i);
			if(ret == -1)
				break;
		}

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return -1;
		}

		return ret;
	}

	int Smp86x::writeRawBit(int slave, int addr, int state)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return -1;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return -1;

		modbus_set_slave(m_modbus, slave);
		ret = modbus_write_bit(m_modbus, addr, state);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return -1;
		}

		return ret;
	}

	int Smp86x::readRawBits(int slave, int addr, int nb, uchar* bits)
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return -1;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return -1;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_read_bits(m_modbus, addr, nb, bits);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return -1;
		}

		return ret;
	}

	void Smp86x::hitHeader( int slave, int header, int delay )
	{
		int ret = 0;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;

		short data[] = {1, header, delay};
		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_registers(m_modbus, 0x200, 3, (ushort*)data);
	}

	void Smp86x::setOutput( int slave, int port, int value )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_write_bit(m_modbus, port+20, value);

		//if (ret == -1)
		//{
		//	bTimeout = true;
		//	time.restart();
		//}
	}

	void Smp86x::getOutputs( int slave, ushort* value )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = 0;
		//bTimeout = false;
		uchar d[16];

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_read_bits(m_modbus, 16, 16, d);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		*value = 0;
		for(int i=0; i<16; i++)
			*value |= (d[i]&0x1)<<i;
	}

	void Smp86x::getInput( int slave, int port, int* value )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = 0;
		//bTimeout = false;
		uchar d;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_read_bits(m_modbus, port, 1, &d);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		*value = d;
	}

	void Smp86x::getInputs( int slave, ushort* value )
	{
		//if (bTimeout && time.elapsed() < 1000)
		//	return;

		int ret = 0;
		//bTimeout = false;
		uchar d[16];

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return;

		modbus_set_slave( m_modbus, slave );
		ret = modbus_read_bits(m_modbus, 0, 16, d);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return;
		}

		*value = 0;
		for(int i=0; i<16; i++)
			*value |= (d[i]&0x1)<<i;
	}

	int Smp86x::writeRawBits( int slave, int addr, int nb, const uchar* data )
	{
		int ret = 0;
		//bTimeout = false;

		QMutexLocker l(&mutex);
		if(!m_modbus)
			return -1;

		modbus_set_slave(m_modbus, slave);
		ret = modbus_write_bits(m_modbus, addr, nb, data);

		if (ret == -1)
		{
			//bTimeout = true;
			//time.restart();
			return -1;
		}

		return ret;
	}

//}


extern "C" {
	void busMonitorAddItem( uint8_t /*isRequest*/, uint8_t /*slave*/, uint8_t /*func*/, uint16_t /*addr*/, uint16_t /*nb*/, uint16_t /*expectedCRC*/, uint16_t /*actualCRC*/ )
	{
	}

	void busMonitorRawData( uint8_t * /*data*/, uint8_t /*dataLen*/, uint8_t /*addNewline*/ )
	{
	}
}
