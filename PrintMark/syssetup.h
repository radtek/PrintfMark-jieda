#ifndef SYSSETUP_H
#define SYSSETUP_H

#include <QDialog>
namespace Ui {class SysSetup;};

class SysSetup : public QDialog
{
	Q_OBJECT

public:
	SysSetup(QWidget *parent = 0);
	~SysSetup();

	void accept();
private:
	Ui::SysSetup *ui;
};

#endif // SYSSETUP_H
