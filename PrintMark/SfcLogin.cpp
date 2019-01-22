#include "stdafx.h"
#include "SfcLogin.h"
#include "ui_SfcLogin.h"

SfcLogin::SfcLogin(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::SfcLogin();
	ui->setupUi(this);
}

SfcLogin::~SfcLogin()
{
	delete ui;
}

QString SfcLogin::getName() const
{
	return ui->lineEdit->text();
}
