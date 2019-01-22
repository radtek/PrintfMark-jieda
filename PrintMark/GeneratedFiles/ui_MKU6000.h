/********************************************************************************
** Form generated from reading UI file 'MKU6000.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MKU6000_H
#define UI_MKU6000_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MKU6000
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *MKU6000)
    {
        if (MKU6000->objectName().isEmpty())
            MKU6000->setObjectName(QStringLiteral("MKU6000"));
        MKU6000->resize(1472, 777);
        label = new QLabel(MKU6000);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(760, -230, 841, 929));
        label->setPixmap(QPixmap(QString::fromUtf8(":/2.png")));
        label_2 = new QLabel(MKU6000);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 831, 781));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/1.png")));

        retranslateUi(MKU6000);

        QMetaObject::connectSlotsByName(MKU6000);
    } // setupUi

    void retranslateUi(QDialog *MKU6000)
    {
        MKU6000->setWindowTitle(QApplication::translate("MKU6000", "MKU6000", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MKU6000: public Ui_MKU6000 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MKU6000_H
