#ifndef smp86xlib_h__
#define smp86xlib_h__

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

class __declspec(dllimport) Smp86x
{
public:
	static Smp86x* create(const char* comport, int baudrate, int timeout = 50);
	static Smp86x* create(const char*host, const char* port, int timeout = 50);
	void destroy();

	bool isOpen() const;
	bool isRunning(int slave, int axis) const;
	int home(int slave, int axis);

	int stop(int slave, int axis);
	int stopAll(int slave = 0xa);

	int getCounter(int slave, int axis, int* pos, int* ppos = NULL);
	int setCounter(int slave, int axis, int pos);

	int start(int slave, int axis, int dist, int svel, int cvel, double acc);
	int start(int slave, int axis, int svel, int cvel, double acc);
	int start(int slave, int axis1, int axis2, int dist1, int dist2, int svel, int cvel, double acc);
	int start(int slave, int axis1, int axis2, int axis3, int dist1, int dist2, int dist3, int svel, int cvel, double acc);
	int changeSpeed(int slave, int axis, int vel);

	int setPWM(int slave, int port, int value);
	int setOutput(int slave, int port, int value);
	int getOutputs(int slave, ulong* value);
	int getInput(int slave, int port, int* value);
	int getInputs(int slave, ulong* value);

	int writeRawData(int slave, int addr, int nb, ushort* data);
	int readRawData(int slave, int addr, int nb, ushort* data);
	int writeRawBit(int slave, int addr, int state);
	int writeRawBits(int slave, int addr, int nb, const uchar* data);
	int readRawBits(int slave, int addr, int nb, uchar* bits);
};

#endif // smp86xlib_h__
