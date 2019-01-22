#pragma once

#include "ui_PassWordDialog.h"
#include "ui_NewPassWordDialog.h"

class PassWordDialog : public QDialog, public Ui::PassWordDialog
{
	Q_OBJECT
public:
	PassWordDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

	void setPassWordString(const QString& password);
public slots:
	void on_toolButton_clicked();
	void accept();
private:
	QString password;
};


class NewPassWordDialog : public QDialog, public Ui::NewPassWordDialog
{
	Q_OBJECT
public:
	NewPassWordDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void setOldPassWordString(const QString& oldPassWord);
	QString getNewPassWordString() const;
	public slots:
		void accept();
protected:
private:
	QString oldPassWord;
	QString newPassWord;
};