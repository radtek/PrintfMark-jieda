#include "stdafx.h"
#include "PassWordDialog.h"

PassWordDialog::PassWordDialog( QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
:QDialog(parent, f|Qt::MSWindowsFixedSizeDialogHint)
{
	setupUi(this);
}

void PassWordDialog::setPassWordString( const QString& password )
{
	this->password = password;
}

void PassWordDialog::accept()
{
	QCryptographicHash crypto(QCryptographicHash::Md5);
	crypto.addData(QByteArray().append(lineEdit->text()));
	if (crypto.result() != password && !password.isEmpty())
	{
		QMessageBox::warning(this, windowTitle(), QString::fromUtf16(L"密码错误!"));
		lineEdit->selectAll();
		lineEdit->setFocus();
	}
	else
	{
		QDialog::accept();
	}
}

void PassWordDialog::on_toolButton_clicked()
{
	QAction* action = QMenu::exec(QList<QAction*>() << actionPasswd, QCursor::pos());
	if(action == actionPasswd)
	{
		QSettings settings;
		NewPassWordDialog newPassword(this);
		newPassword.setOldPassWordString(settings.value("password", "\xd4\x1d\x8c\xd9\x8f").toString());
		if (QDialog::Accepted == newPassword.exec())
		{
			settings.setValue("password", newPassword.getNewPassWordString());
			return QDialog::accept();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

NewPassWordDialog::NewPassWordDialog( QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
	:QDialog(parent, f|Qt::MSWindowsFixedSizeDialogHint)
{
	setupUi(this);
}

void NewPassWordDialog::setOldPassWordString( const QString& oldPassWord )
{
	this->oldPassWord = oldPassWord;
}

QString NewPassWordDialog::getNewPassWordString() const
{
	QCryptographicHash crypto(QCryptographicHash::Md5);
	crypto.addData(QByteArray().append(leNewPassWord->text()));
	return crypto.result();
}

void NewPassWordDialog::accept()
{
	QCryptographicHash crypto(QCryptographicHash::Md5);
	crypto.addData(QByteArray().append(leOldPassWord->text()));

	if (crypto.result() != oldPassWord /*&& !oldPassWord.isEmpty() && leOldPassWord->text() != "666666"*/)
	{
		QMessageBox::warning(this, windowTitle(), QString::fromUtf16(L"原密码不正确!"));
		leOldPassWord->selectAll();
		leCfmPassWord->clear();
		leNewPassWord->clear();
		leOldPassWord->setFocus();
	}
	else if (leCfmPassWord->text() != leNewPassWord->text())
	{
		QMessageBox::warning(this, windowTitle(), QString::fromUtf16(L"两次密码输入不相同!"));
		leOldPassWord->clear();
		leCfmPassWord->clear();
		leNewPassWord->clear();
		leOldPassWord->setFocus();
	}
	else
	{
		QDialog::accept();
	}
}