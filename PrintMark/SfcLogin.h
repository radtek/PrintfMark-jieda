#pragma once

#include <QDialog>
namespace Ui { class SfcLogin; };

class SfcLogin : public QDialog
{
	Q_OBJECT

public:
	SfcLogin(QWidget *parent = Q_NULLPTR);
	~SfcLogin();

	QString getName() const;
private:
	Ui::SfcLogin *ui;
};
