#include "stdafx.h"
#include "printmark.h"
#include "dbghelp.h"
#include <QtWidgets/QApplication>

//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "WTxRTE.lib")
#pragma comment(lib, "dbghelp")
extern "C" namespace RTEdcsn
{
	// 回调模式
	typedef void(*Func)(WPARAM wParam, LPARAM lParam);
	void initialize1(const char* pCLSID, const char* pLicenceFile = NULL, const DWORD dwDelay = 0, const DWORD dwCallbackDelay = 1000, Func pf = NULL);
	// pCLSID：软件标识（唯一，不允许空格）
	// pLicenceFile：授权文件名称，如"walscan.lic"，文件放在运行目录；若为NULL则默认为"Licence.lic"
	// dwDelay：软件狗判断延迟，毫秒
	// dwCallbackDelay：允许回调操作时间，毫秒
	// pf：回调函数

	// 消息模式
	void initialize2(const char* pCLSID, const char* pLicenceFile = NULL, const DWORD dwDelay = 0, const DWORD dwMessageDelay = 1000, const HWND hNotifyWnd = NULL, const UINT uMessageID = 0);
	// pCLSID：软件标识（唯一，不允许空格）
	// pLicenceFile：授权文件名称，如"walscan.lic"，文件放在运行目录；若为NULL则默认为"Licence.lic"
	// dwDelay：软件狗判断延迟，毫秒
	// dwMessageDelay：允许消息响应时间，毫秒
	// hNotifyWnd：消息接收窗口句柄
	// uMessageID：消息ID

	// 回调模式/消息模式下wParam：退出代码
	// 回调模式/消息模式下lParam：允许时间
	QMainWindow* mainWindow = NULL;
}

void _rtedcsn_func(WPARAM nExitCode, LPARAM dDelayTime)
{
	::MessageBox((RTEdcsn::mainWindow && IsWindow((HWND)RTEdcsn::mainWindow->winId())) ? (HWND)RTEdcsn::mainWindow->winId() : NULL, QObject::tr("代码%1").arg(int(nExitCode)).utf16(), QObject::tr("错误").utf16(), MB_OK);
	if (qApp) qApp->quit();
	::Sleep(dDelayTime);
}

LONG WINAPI TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *pExceptionInfo)
{
	HANDLE hFile = CreateFile(L"crash.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;
	stExceptionParam.ThreadId = GetCurrentThreadId();
	stExceptionParam.ExceptionPointers = pExceptionInfo;
	stExceptionParam.ClientPointers = FALSE;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &stExceptionParam, NULL, NULL);
	CloseHandle(hFile);
	::MessageBox(NULL, L"程序出现异常, 需要关闭!", L"致命错误", MB_OK);
	return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
	SetUnhandledExceptionFilter(TopLevelExceptionFilter);
	QApplication a(argc, argv);
	//QDate date = QDate(2024, 3, 21);
	//const char d[] = "0123456789ABCDEFGHJKLMNPQRSTUWXY";
	//QMessageBox::information(NULL, "ff", QString("F0P%1%2%3").arg(date.year()-2010, 0, 16).arg(d[date.month()]).arg(d[date.day()]).toUpper());
	//return 0;

	QTranslator *translator = new QTranslator(&a);
	if (translator->load("lang_cn.qm"))
		a.installTranslator(translator);

	QApplication::setApplicationName(QFileInfo(QApplication::applicationFilePath()).completeBaseName());
	QApplication::setOrganizationName(".");

	QSettings::setDefaultFormat(QSettings::IniFormat);
	QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());
	//QMessageBox::information(nullptr, "", "");
	//QMessageBox::information(NULL, "", "aaa");
	QSettings settings;

	if (!settings.value("save_close", false).toBool())
		QMessageBox::warning(NULL, QString::fromUtf16(L"警告"), QString::fromUtf16(L"上一次程序非正常退出, 配置文件可能不完整, 请确认!"));
	else
		QFile::copy(QFileInfo(QApplication::applicationFilePath()).completeBaseName() + ".ini", QFileInfo(QApplication::applicationFilePath()).completeBaseName()+"_bak.ini");
	settings.setValue("save_close", false);
	PrintMark w;
	w.showMaximized();
//  #ifdef WTxRTE
//  	RTEdcsn::mainWindow = &w;
//  	RTEdcsn::initialize1("PrintMark", NULL, 2000, 10000, _rtedcsn_func);
//  #endif // WTxRTE
//  	//a.connect(&a, &QApplication::aboutToQuit, &w, &QMainWindow::close);
	return a.exec();
}
