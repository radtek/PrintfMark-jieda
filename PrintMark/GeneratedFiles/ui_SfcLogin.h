/********************************************************************************
** Form generated from reading UI file 'SfcLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SFCLOGIN_H
#define UI_SFCLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SfcLogin
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SfcLogin)
    {
        if (SfcLogin->objectName().isEmpty())
            SfcLogin->setObjectName(QStringLiteral("SfcLogin"));
        SfcLogin->resize(201, 71);
        verticalLayout = new QVBoxLayout(SfcLogin);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SfcLogin);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(SfcLogin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(SfcLogin);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        buttonBox = new QDialogButtonBox(SfcLogin);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);

        QWidget::setTabOrder(lineEdit, pushButton);

        retranslateUi(SfcLogin);
        QObject::connect(pushButton, SIGNAL(clicked()), SfcLogin, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), SfcLogin, SLOT(accept()));

        QMetaObject::connectSlotsByName(SfcLogin);
    } // setupUi

    void retranslateUi(QDialog *SfcLogin)
    {
        SfcLogin->setWindowTitle(QApplication::translate("SfcLogin", "\346\223\215\344\275\234\345\221\230\347\231\273\345\275\225", nullptr));
        label->setText(QApplication::translate("SfcLogin", "\346\223\215\344\275\234\345\221\230:", nullptr));
        pushButton->setText(QApplication::translate("SfcLogin", "\347\246\273\347\272\277\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SfcLogin: public Ui_SfcLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SFCLOGIN_H
