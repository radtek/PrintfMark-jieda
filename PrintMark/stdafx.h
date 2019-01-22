#define _STDAFX_H
#include <WinSock2.h>
#include <Windows.h>

//#define BarcodePrintService
#define FoxlinkAdd
#define dalay_broad   300
#ifdef min
#undef min
#endif

#include "config.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QtConcurrent>

//#pragma pack(push)
//#pragma pack(2)
//#define SMP86X_STATUS_ADDRESS	0x20
//struct AXIS_STATUS
//{
//	long logicPos;
//	long realPos;
//	unsigned short state; //高8位:[ALM/EMG/EL-/EL+/IN3/IN2/IN1/IN0]低8位:[/////RESERVE/ERR/DRV]
//};
//
//struct SMP86X_STATUS	//最大空间96字节
//{
//	AXIS_STATUS axis_status[4];	//各轴状态
//	long inputs;				//DI状态
//	long outputs;				//DO状态
//};
//#pragma pack(pop)

#include "smp86xlib.h"
#include "smp86xhandler.h"
#pragma comment(lib, "smp86xlib")

inline bool isRunning(const SMP86X_STATUS& ss)
{
	bool ret = false;
	for(int i=0; i<4; i++)
		if(!(ss.axis_status[i].state & 0x80) && (ss.axis_status[i].state & 0x1))
			return true;
	return false;
}

typedef struct tagSPEEDPARAM
{
	struct {
		double sv;
		double v;
		double a;
	} axis[6];
} SPEEDPARAM;

extern SPEEDPARAM speeds[];

//////////////////////////////////////////////////////////////////////////
inline bool sendTcpData(QTcpSocket* socket, int m)
{
	if(socket->state() != QAbstractSocket::ConnectedState)
		return false;

	//while(!socket->atEnd())
		socket->readAll();

#ifdef _OLD_VERSION
	//socket->write(m==0 ? "Q" : "T");
	switch(m)
	{
	case 0:
		socket->write("check 0");
		break;
	case 1:
		socket->write("check 1");
		break;
	case 2:
		socket->write("check 2");
		break;
	}
#else
	QByteArray buff = QString("$B*q%1$E*").arg(m, 2, 10, QChar('0')).toLatin1();
	socket->write(buff);
#endif // _OLD_VERSION
	return socket->waitForBytesWritten(3000);
}

inline bool readTcpData( QTcpSocket* socket, double* x, double* y, double* a)
{
	if(socket->state() != QAbstractSocket::ConnectedState)
		return false;

	//QTime t;
	//t.start();
	//while(t.elapsed() < 3000 && !socket->canReadLine())
	//	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	socket->waitForReadyRead(2000);
	//while(!socket->canReadLine() && socket->waitForReadyRead(10))
	//	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

// 	if(socket->canReadLine())
// 	{
		QRegExp rx("[+-]?(\\d+\\.?\\d*)");
		QByteArray line = socket->readAll();
		int pos = 0;
		pos = rx.indexIn(line, pos);
		if(pos != -1) *x = rx.cap(0).toDouble();
		else return false;

		pos = rx.indexIn(line, pos+rx.cap(0).length());
		if(pos != -1) *y = rx.cap(0).toDouble();
		else return false;

		pos = rx.indexIn(line, pos+rx.cap(0).length());
		if(pos != -1) *a = rx.cap(0).toDouble();
		else return false;

		return true;
/*	}*/
	return false;
}

inline bool sendPrintData(QIODevice* device, const QByteArray& data)
{
	device->write(data);
	device->waitForBytesWritten(1000);
	if (device->waitForReadyRead(1000))
		return device->readAll().startsWith("\x06");
	return false;
}

inline bool sendInkData(QIODevice* device, const QByteArray& data)
{
	device->write(data);
	device->waitForBytesWritten(1000);
	if (device->waitForReadyRead(1000))
		return device->readAll().startsWith("");
	return false;
}

inline bool receivrSUCFlag(QIODevice* device)
{
	if (device->waitForReadyRead(2500))
		return device->readAll().startsWith("\x32");
	return false;
}

inline QTransform qTransformFromByteArray(const QByteArray& ba)
{
	QDataStream stream(ba);
	QTransform t;
	stream >> t;
	return t;
}

inline QByteArray qTransformToByteArray(const QTransform& t)
{
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << t;
	return ba;
}

#if 0
// OpenCV struct
#pragma region
typedef struct CvMat
{
	int type;
	int step;

	/* for internal use only */
	int* refcount;
	int hdr_refcount;

	union
	{
		uchar* ptr;
		short* s;
		int* i;
		float* fl;
		double* db;
	} data;

#ifdef __cplusplus
	union
	{
		int rows;
		int height;
	};

	union
	{
		int cols;
		int width;
	};
#else
	int rows;
	int cols;
#endif

}
CvMat;

typedef struct CvPoint2D32f
{
	float x; /* X坐标, 通常以0为基点*/
	float y; /* Y坐标, 通常以0为基点*/
}CvPoint2D32f;
#pragma endregion

inline QTransform vector_to_hom_mat2d(const QPointF p[], const QPointF q[])
{
#ifdef _DEBUG
	HMODULE hModule = ::LoadLibrary(L"opencv_imgproc246d.dll");
	HMODULE hModule1 = ::LoadLibrary(L"opencv_core246d.dll");
#else
	HMODULE hModule = ::LoadLibrary(L"opencv_imgproc246.dll");
	HMODULE hModule1 = ::LoadLibrary(L"opencv_core246.dll");
#endif // _DEBUG
	QTransform trans;

	if(hModule && hModule1)
	{
		CvPoint2D32f src[3], dst[3];
		src[0].x = p[0].x(), src[0].y = p[0].y();
		src[1].x = p[1].x(), src[1].y = p[1].y();
		src[2].x = p[2].x(), src[2].y = p[2].y();
		dst[0].x = q[0].x(), dst[0].y = q[0].y();
		dst[1].x = q[1].x(), dst[1].y = q[1].y();
		dst[2].x = q[2].x(), dst[2].y = q[2].y();
		auto cvCreateMat = (CvMat* (*)(int rows, int cols, int type))::GetProcAddress(hModule1, "cvCreateMat");
		auto cvReleaseMat = (void (*)(CvMat** mat))::GetProcAddress(hModule1, "cvReleaseMat");
		auto cvGetAffineTransform = (CvMat* (*)(CvPoint2D32f src[], CvPoint2D32f dst[], CvMat* map_matrix))::GetProcAddress(hModule, "cvGetAffineTransform");
		if(cvGetAffineTransform && cvCreateMat && cvReleaseMat)
		{
			CvMat* mat = cvCreateMat(2, 3, 5);
			cvGetAffineTransform(src, dst, mat);
			trans = QTransform(mat->data.fl[0], mat->data.fl[3], mat->data.fl[1], mat->data.fl[4], mat->data.fl[2], mat->data.fl[5]);
			cvReleaseMat(&mat);
		}
		FreeLibrary(hModule);
		FreeLibrary(hModule1);
	}
	return trans;
}
#endif // 0

inline void affine_trans_xyu(const QTransform& t, const QPointF& xy, float u, QPointF& xy1, float& u1)
{
	QPointF p0 = xy+QPointF(sin(u), cos(u));
	QLineF l = t.map(QLineF(xy, p0));
	xy1 = l.p1();
	u1 = l.angle()*M_PI/180.0;
	u1 = (u1 > M_PI) ? (u1 - M_PI*2) : u1;
}

inline bool vector_to_rigid(const QPointF& p1, const QPointF& p2, const QPointF& q1, const QPointF& q2, QTransform& trans)
{
	trans = QTransform().translate(q1.x(), q1.y()).rotate(QLineF(q1, q2).angleTo(QLineF(p1, p2))).translate(-p1.x(), -p1.y());
	return true;
	//QPolygonF pg1 = genQuad(p1, p2);
	//pg1 = QTransform().translate(p1.x(), p1.y()).scale(sqrt(1.0/distance_pp(p1, p2)), sqrt(1.0/distance_pp(p1, p2))).translate(-p1.x(), -p1.y()).map(pg1);
	//QPolygonF pg2 = genQuad(q1, q2);
	//pg2 = QTransform().translate(q1.x(), q1.y()).scale(sqrt(1.0/distance_pp(q1, q2)), sqrt(1.0/distance_pp(q1, q2))).translate(-q1.x(), -q1.y()).map(pg2);
	//return QTransform::quadToQuad(pg1, pg2, trans);

}

inline QTransform vector_angle_to_rigid(const QVector3D& v1, const QVector3D& v2)
{
	return QTransform().translate(v2.x(), v2.y()).rotate(v2.z()-v1.z()).translate(-v1.x(), -v1.y());
}

inline double normalizeAngle(double angle)
{
	while (angle > 180) angle -= 360; while (angle < -180)angle += 360;
	return angle;
}

/*#ifdef _FOXLINK*/
#define _CODE_LENGTH 4
// inline QByteArray nextCode(const QByteArray& code = "0000")
// {
 	static const QByteArray c("0123456789ABCDEFGHJKLMNPQRSTUVWXYZ");
// 	if(code.size() != 4)
// 		return QByteArray("0001");
// 
// 	QByteArray newCode("0000");
// 	int carry = 1;
// 	for (int i=3; i>=0; i--)
// 	{
// 		int p = c.indexOf(code[i]);
// 		newCode[i] = c[((p+carry)%c.size())];
// 		carry = (p+carry)/c.size();
// 	}
// 	return newCode;
// }

// #define _CODE_LENGTH 6
//  static const QByteArray c("0123456789");
//   // _FOXLINK
inline QByteArray nextCode(const QByteArray& code = QByteArray())
{
	QByteArray newCode(_CODE_LENGTH, c[0]);
	if (code.size() != _CODE_LENGTH)
		return newCode;

	int carry = 1;
	for (int i=_CODE_LENGTH-1; i>=0; i--)
	{
		int p = c.indexOf(code[i]);
		newCode[i] = c[((p+carry)%c.size())];
		carry = (p+carry)/c.size();
	}
	return newCode;
}

typedef struct _PRINTINFO
{
	QString panel_no;
	QString bound_serial;
	QStringList child_serial;
	QStringList child_state;
	int index;
} PRINTINFO;
