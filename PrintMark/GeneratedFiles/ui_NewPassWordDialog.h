/********************************************************************************
** Form generated from reading UI file 'NewPassWordDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORDDIALOG_H
#define UI_NEWPASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NewPassWordDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leOldPassWord;
    QLabel *label_2;
    QLineEdit *leNewPassWord;
    QLabel *label_3;
    QLineEdit *leCfmPassWord;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewPassWordDialog)
    {
        if (NewPassWordDialog->objectName().isEmpty())
            NewPassWordDialog->setObjectName(QStringLiteral("NewPassWordDialog"));
        NewPassWordDialog->resize(220, 124);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/20130104095015810_easyicon_cn_64.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewPassWordDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(NewPassWordDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(NewPassWordDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leOldPassWord = new QLineEdit(NewPassWordDialog);
        leOldPassWord->setObjectName(QStringLiteral("leOldPassWord"));
        leOldPassWord->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(leOldPassWord, 0, 1, 1, 1);

        label_2 = new QLabel(NewPassWordDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leNewPassWord = new QLineEdit(NewPassWordDialog);
        leNewPassWord->setObjectName(QStringLiteral("leNewPassWord"));
        leNewPassWord->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(leNewPassWord, 1, 1, 1, 1);

        label_3 = new QLabel(NewPassWordDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        leCfmPassWord = new QLineEdit(NewPassWordDialog);
        leCfmPassWord->setObjectName(QStringLiteral("leCfmPassWord"));
        leCfmPassWord->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(leCfmPassWord, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(NewPassWordDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(NewPassWordDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewPassWordDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewPassWordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewPassWordDialog);
    } // setupUi

    void retranslateUi(QDialog *NewPassWordDialog)
    {
        NewPassWordDialog->setWindowTitle(QApplication::translate("NewPassWordDialog", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        label->setText(QApplication::translate("NewPassWordDialog", "\345\216\237\345\257\206\347\240\201", nullptr));
        label_2->setText(QApplication::translate("NewPassWordDialog", "\346\226\260\345\257\206\347\240\201", nullptr));
        label_3->setText(QApplication::translate("NewPassWordDialog", "\346\226\260\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewPassWordDialog: public Ui_NewPassWordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORDDIALOG_H
