/********************************************************************************
** Form generated from reading UI file 'PassWordDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDIALOG_H
#define UI_PASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PassWordDialog
{
public:
    QAction *actionPasswd;
    QVBoxLayout *vboxLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PassWordDialog)
    {
        if (PassWordDialog->objectName().isEmpty())
            PassWordDialog->setObjectName(QStringLiteral("PassWordDialog"));
        PassWordDialog->resize(205, 69);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/20130104095015810_easyicon_cn_64.png"), QSize(), QIcon::Normal, QIcon::Off);
        PassWordDialog->setWindowIcon(icon);
        actionPasswd = new QAction(PassWordDialog);
        actionPasswd->setObjectName(QStringLiteral("actionPasswd"));
        vboxLayout = new QVBoxLayout(PassWordDialog);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        lineEdit = new QLineEdit(PassWordDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEchoMode(QLineEdit::Password);

        vboxLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton = new QToolButton(PassWordDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setAutoRaise(true);
        toolButton->setArrowType(Qt::DownArrow);

        horizontalLayout->addWidget(toolButton);

        buttonBox = new QDialogButtonBox(PassWordDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        vboxLayout->addLayout(horizontalLayout);


        retranslateUi(PassWordDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PassWordDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PassWordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PassWordDialog);
    } // setupUi

    void retranslateUi(QDialog *PassWordDialog)
    {
        PassWordDialog->setWindowTitle(QApplication::translate("PassWordDialog", "\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        actionPasswd->setText(QApplication::translate("PassWordDialog", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PassWordDialog: public Ui_PassWordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDIALOG_H
